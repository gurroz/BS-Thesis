

#include "interpoladorMixto.h"
#include <limits>


InterpoladorMixto::InterpoladorMixto(){

};

bool PointInTextureTriangle(Nodo *p, Nodo *a, Nodo *b, Nodo *c){

    // Compute vectors
    double v0x = c->getTextureX() - a->getTextureX();
    double v0y = c->getTextureY() - a->getTextureY();
    double v1x = b->getTextureX() - a->getTextureX();
    double v1y = b->getTextureY() - a->getTextureY();
    double v2x = p->getTextureX() - a->getTextureX();
    double v2y = p->getTextureY() - a->getTextureY();

    // Compute dot products
    double dot00 = v0x*v0x + v0y*v0y;
    double dot01 = v0x*v1x + v0y*v1y;
    double dot02 = v0x*v2x + v0y*v2y;
    double dot11 = v1x*v1x + v1y*v1y;
    double dot12 = v1x*v2x + v1y*v2y;

    // Compute barycentric coordinates
    double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    // Check if point is in triangle
    return (u >= -0.00000001) && (v >= -0.00000001) && (u + v <= 1.0000001);
}



void InterpoladorMixto::setearInterpolaciones(Malla *malla, Malla *modelo){

    int *nodos_marcados = malla->getNodos()->nodos_marcados;
    int nnodos = malla->getNodos()->n_marcados;

    vector<int> ind_nodos;

        double minx = numeric_limits<double>::max();
        double maxx = -1*numeric_limits<double>::max();

        double miny = numeric_limits<double>::max();
        double maxy = -1*numeric_limits<double>::max();
        if(malla->tieneTextura()){
            for(int j = 0; j<= modelo->getMaxIndiceNodos(); ++j){
                Nodo *n1 = malla->getNodo( nodos_marcados[j] );

                double x1 = n1->getTextureX();

                double y1 = n1->getTextureY();

                minx = min<double>(x1, minx);
                maxx = max<double>(x1, maxx);

                miny = min<double>(y1, miny);
                maxy = max<double>(y1, maxy);

            }
        }
        for(int i = 0; i<=malla->getMaxIndiceNodos(); ++i){
            Nodo *n = malla->getNodo(i);
            /*if(n->getPunto().getY() < modelo->getNodos()->get_miny()){
                continue;
            }*/

            Vect v(n->getPunto());
            if(malla->tieneTextura()){
                double txx = n->getTextureX(); double txy = n->getTextureY();
                if(txx < minx || txx > maxx || txy > maxy){
                     continue;
                }

                bool bien = false;

                if(txy >= miny){
                    for(int j = 0; j<= modelo->getMaxIndiceCaras(); ++j){
                        Cara *c = modelo->getCara(j);
                        ind_nodos = c->getNodos();
                        Nodo *n1 = malla->getNodo( nodos_marcados[ind_nodos[0]] );
                        Nodo *n2 = malla->getNodo( nodos_marcados[ind_nodos[1]] );
                        Nodo *n3 = malla->getNodo( nodos_marcados[ind_nodos[2]] );

                        if(PointInTextureTriangle(n, n1,n2,n3)){
                            bien = true;
                            break;
                        }
                    }
                }

                if(!bien){         /** SI NO BIEN, ASIGNAR VALOR CON 2 MAS CERCANOS!! */
                    float dist1 = numeric_limits<float>::max();
                    float dist2 = numeric_limits<float>::max();
                    int i1 = 0, i2 = 0;
                    for(int j = 0; j< nnodos; ++j){
                        Nodo *otroNodo = malla->getNodo(nodos_marcados[j]);
                        double tx = n->getTextureX(), ty = n->getTextureY();
                        double otx = otroNodo->getTextureX(), oty = otroNodo->getTextureY();
                        float newDist = (tx-otx)*(tx-otx) + (ty-oty)*(ty-oty);
                        if(newDist<=dist2){
                            if(malla->existeCaminoEntre(i, nodos_marcados[j]) ){
                                if( newDist <= dist1){
                                    dist2 = dist1;
                                    i2 = i1;
                                    dist1 = newDist;
                                    i1 = j;
                                }else if(newDist <= dist2){
                                    dist2 = newDist;
                                    i2 = j;
                                }
                            }
                        }
                    }
                    if(i1 == 0 && i2 == 0) continue;
                    double dist = (dist1 + dist2);
                    double coef = 0.8-dist>0?0.8-dist:0.0;
                    coef = coef*coef/dist;
                    n->asociarNodos(nodos_marcados[i1], (dist2)*coef, nodos_marcados[i2], (dist1)*coef , 0, 0);

                    continue;
                }   /*** FIN NO-BIEN */
            }


            bool esUnNodo = false;
            for(int j = 0; j< nnodos; ++j){
                if(i == nodos_marcados[j]){
                    esUnNodo = true;
                    break;
                }
            }
             if(esUnNodo){
                n->asociarNodos(i, 1.0f, 0, 0.0f, 0, 0.0f);
                continue;
             }

            int i1 = 0;
            int i2 = 0;
            int i3 = 0;

            /**  VER QUE ESTA EN EL TRIANGULO  */

            vector<int> ind_nodos;
            float dist = numeric_limits<float>::max();

            for(int j = 0; j<= modelo->getMaxIndiceCaras(); ++j){
                Cara *c = modelo->getCara(j);
                ind_nodos = c->getNodos();
                Nodo *n1 = malla->getNodo( nodos_marcados[ ind_nodos[0] ] );
                Nodo *n2 = malla->getNodo( nodos_marcados[ ind_nodos[1] ] );
                Nodo *n3 = malla->getNodo( nodos_marcados[ ind_nodos[2] ] );

                Vect v1(n1->getPunto());
                Vect v2(n2->getPunto());
                Vect v3(n3->getPunto());
                float newDist = (v1-v).largo() + (v2-v).largo() + (v3-v).largo();
                if(newDist < dist){

                    if(!v.estaEnTriangulo(v1,v2,v3)) continue;

                    bool estaConectado = true;
                    for(int kl = 0; kl<3; ++kl){
                        if(! malla->existeCaminoEntre(i, nodos_marcados[ind_nodos[kl]]) ){
                            estaConectado = false;
                            break;
                        }
                    }
                    if(!estaConectado) continue;

                    dist = newDist;

                    i1 = ind_nodos[0];
                    i2 = ind_nodos[1];
                    i3 = ind_nodos[2];
                }
            }
            if(i1 == 0 && i2 == 0 && i3 == 0){
                    continue;
            }

            /** //////////////////////////////*/


             Nodo *nodo_close1 = malla->getNodo(nodos_marcados[i1]);
             Nodo *nodo_close2 = malla->getNodo(nodos_marcados[i2]);
             Nodo *nodo_close3 = malla->getNodo(nodos_marcados[i3]);

             Vect vec(n->getPunto());
             Vect v1(nodo_close1->getPunto());
             Vect v2(nodo_close2->getPunto());
             Vect v3(nodo_close3->getPunto());
             Vect vproyectado = vec.proyectadoEn(v1,v2,v3);

            /*****************************  NODOS CERCANOS ESTABLECER*/

            double  a11, a12, a13, a21, a22, a23, a31, a32, a33;
            a11 = v1.getPunto().getX();
            a21 = v1.getPunto().getY();
            a31 = v1.getPunto().getZ();

            a12 = v2.getPunto().getX();
            a22 = v2.getPunto().getY();
            a32 = v2.getPunto().getZ();

            a13 = v3.getPunto().getX();
            a23 = v3.getPunto().getY();
            a33 = v3.getPunto().getZ();

            double x = vproyectado.getPunto().getX();
            double y = vproyectado.getPunto().getY();
            double z = vproyectado.getPunto().getZ();

            double det = a11*(a33*a22-a32*a23)-a21*(a33*a12-a32*a13)+a31*(a23*a12-a22*a13);
            double coef1 = (a33*a22-a32*a23)*x -(a33*a12-a32*a13)*y + (a23*a12-a22*a13)*z;
            double coef2 = -(a33*a21-a31*a23)*x + (a33*a11-a31*a13)*y -(a23*a11-a21*a13)*z;
            double coef3 =  (a32*a21-a31*a22)*x -(a32*a11-a31*a12)*y + (a22*a11-a21*a12)*z;

            n->asociarNodos(nodos_marcados[i1], coef1/det, nodos_marcados[i2], coef2/det, nodos_marcados[i3], coef3/det);

            /*********************** FIN ESTABLECER */
        }
};

InterpoladorMixto::~InterpoladorMixto(){

};
