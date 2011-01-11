

#include "interpoladorNodosCercanos.h"
#include <limits>


InterpoladorNodosCercanos::InterpoladorNodosCercanos(){

};

void InterpoladorNodosCercanos::setearInterpolaciones(Malla *malla, Malla *modelo){

            int counterr = 0;

    int *nodos_marcados = malla->getNodos()->nodos_marcados;
    int nnodos = malla->getNodos()->n_marcados;

    vector<int> ind_nodos;


    for(int i = 0; i<=malla->getMaxIndiceNodos(); ++i){
            Nodo *n = malla->getNodo(i);

            bool la = false;
            for(int j = 0; j< nnodos; ++j){
                if(i == nodos_marcados[j]){
                    la = true;
                    break;
                }
            }
             if(la){
                n->asociarNodos(i, 1.0f, 0, 0.0f, 0, 0.0f);
                continue;
             }

            int i1 = 0;
            int i2 = 0;
            int i3 = 0;


            /** 3 PUNTOS MAS CERCANOS!*/
            float dist1 = numeric_limits<float>::max();
            float dist2 = numeric_limits<float>::max();
            float dist3 = numeric_limits<float>::max();

            for(int j = 0; j< nnodos; ++j){
                Nodo *otroNodo = malla->getNodo(nodos_marcados[j]);
                //float newDist = n->distancia(otroNodo);
                double tx = n->getTextureX(), ty = n->getTextureY();
                double otx = otroNodo->getTextureX(), oty = otroNodo->getTextureY();
                float newDist = (tx-otx)*(tx-otx) + (ty-oty)*(ty-oty);
                if(newDist<=dist3){
                    if(! malla->existeCaminoEntre(i, nodos_marcados[j]) ){
                        continue;
                        //cout << "noexiste " << i << "," << nodos_marcados[j] << endl;
                    }
                }
                if( newDist <= dist1){
                    dist3 = dist2;
                    i3 = i2;
                    dist2 = dist1;
                    i2 = i1;
                    dist1 = newDist;
                    i1 = j;
                }else if(newDist <= dist2){
                    dist3 = dist2;
                    i3 = i2;
                    dist2 = newDist;
                    i2 = j;
                }else if(newDist <= dist3){
                    dist3 = newDist;
                    i3 = j;
                }
            }

            if(i1 == 0 && i2 == 0 && i3 == 0){
                    continue;
            }



             //float tot = 3*(dist1 + dist2 + dist3);
             //n->asociarNodos(nodos_marcados[i1], (tot-dist1)/tot, nodos_marcados[i2], (tot-dist2)/tot, nodos_marcados[i3], (tot-dist3)/tot);
             Nodo *nodo_close1 = malla->getNodo(nodos_marcados[i1]);
             Nodo *nodo_close2 = malla->getNodo(nodos_marcados[i2]);
             Nodo *nodo_close3 = malla->getNodo(nodos_marcados[i3]);

             Vect vec(n->getPunto());
             Vect v1(nodo_close1->getPunto());
             Vect v2(nodo_close2->getPunto());
             Vect v3(nodo_close3->getPunto());
             Vect vproyectado = vec.proyectadoEn(v1,v2,v3);


            double  a11, a12, a13, a21, a22, a23, a31, a32, a33;
            //Nodo *v1 = malla->getNodo(nodos_marcados[i1]);
            a11 = v1.getPunto().getX();
            a21 = v1.getPunto().getY();
            a31 = v1.getPunto().getZ();
            //Nodo *v2 = malla->getNodo(nodos_marcados[i2]);
            a12 = v2.getPunto().getX();
            a22 = v2.getPunto().getY();
            a32 = v2.getPunto().getZ();
            //Nodo *v3 = malla->getNodo(nodos_marcados[i3]);
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


        }
};


InterpoladorNodosCercanos::~InterpoladorNodosCercanos(){

};
