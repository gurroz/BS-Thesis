#include "distribuirhormona.h"



DistribuirHormona::DistribuirHormona(Malla* malla, SimpleGLScene* simpleglscene, double factorgravitacional, double factorlongitudinal, double factortangencial):Comando(malla){
    this->simpleglscene=simpleglscene;
    this->factorgravitacional=factorgravitacional;
    this->factorlongitudinal=factorlongitudinal;
    this->factortangencial=factortangencial;
    nodosprob=new vector<NodoProb>[malla->getMaxIndiceNodos()+1];
    }

void DistribuirHormona::execute(){
    //Recalculamos la medula
    cout << "Recalculando medula..." << endl;
    malla->recalcularMedula();


    //Obtengo los nodos cercanos a cada uno de los nodos;
    cout << "Obtengo los nodos cercanos a cada uno..." << endl;

    Nodo* nodo;
    for (int i=0; i<=malla->getMaxIndiceNodos(); i++){
        nodo=malla->getNodo(i);
        if (nodo!=NULL){
            nodosprob[i]=getNodosCercanos(i);
            }
        }


    //Calculamos las probabilidades de moverse a cada uno de los nodos.
    cout << "Calculamos probabilidades..." << endl;
    for (int i=0; i<=malla->getMaxIndiceNodos(); i++){
        Nodo* nodo=malla->getNodo(i);
        if (nodo!=NULL){
            for (int j=0; j<(int)nodosprob[i].size(); j++)
                nodosprob[i][j].probabilidad=calcularProbabilidad(i,nodosprob[i][j].indnodo,nodosprob[i][j].ponderacionubicacion);
            normalizarProbabilidades(i);
            }
        }

    //Ahora hacemos el paseo al azar de las hormonas.
    cout << "Realizamos el paseo al azar..." << endl;
    paseoHormonas();

    }

void DistribuirHormona::normalizarProbabilidades(int indNodo){
    vector<NodoProb> &nodoprob=nodosprob[indNodo];

    double suma=0;
    for (int i=0; i<(int)nodoprob.size(); i++)
        suma=suma+nodoprob[i].probabilidad;

    if (suma==0){
        for (int i=0; i<(int)nodoprob.size(); i++){
            nodoprob[i].probabilidad=1.0;
            suma=suma+nodoprob[i].probabilidad;
            }
        }

    for (int i=0; i<(int)nodoprob.size(); i++)
        nodoprob[i].probabilidad=nodoprob[i].probabilidad/suma;
    }

vector<NodoProb> DistribuirHormona::getNodosCercanos(int indNodo){
    vector<NodoProb> resultado;
    vector<int> nodosCercanos;
    //Agrego nodos del alrededor.
    Nodo* nodo=malla->getNodo(indNodo);
    vector<int> carasvecinas=nodo->getCaras();
    for (int i=0; i<(int)carasvecinas.size(); i++){
        vector<int> puntosdistintos=malla->getCara(carasvecinas[i])->getPuntosDistintos(indNodo);
        nodosCercanos.push_back(puntosdistintos[0]);
        nodosCercanos.push_back(puntosdistintos[1]);
        }

    //Agrego nodos de mas alrededor.
    int nnodosvecindad=nodosCercanos.size();
    for (int j=0; j<nnodosvecindad; j++){
        vector<int> carasvecinas=malla->getNodo(nodosCercanos[j])->getCaras();
        for (int i=0; i<(int)carasvecinas.size(); i++){
            vector<int> puntosdistintos=malla->getCara(carasvecinas[i])->getPuntosDistintos(nodosCercanos[j]);
            nodosCercanos.push_back(puntosdistintos[0]);
            nodosCercanos.push_back(puntosdistintos[1]);
            }
        }


    //Corrijo el vector, eliminando repetidos e indices a indNodo.
    sort(nodosCercanos.begin(),nodosCercanos.end());
    for (int i=0; i<(int)nodosCercanos.size(); i++){
        if(nodosCercanos[i]==indNodo){
            nodosCercanos.erase(nodosCercanos.begin()+i);
            i=-1;
            }
        }
    for (int i=0; i<(int)nodosCercanos.size(); i++){
        if (i+1<(int)nodosCercanos.size() && nodosCercanos[i]==nodosCercanos[i+1]){
            nodosCercanos.erase(nodosCercanos.begin()+i);
            i=-1;
            }
        }






    //Les calculamos las distancias.
    Vect aux;
    for (int i=0; i<(int)nodosCercanos.size(); i++){
        aux=Vect(malla->getNodo(indNodo)->getPunto())-Vect(malla->getNodo(nodosCercanos[i])->getPunto());
        resultado.push_back(NodoProb(nodosCercanos[i],aux.largo()));
        }

    //Seleccionamos los 8 mas cercanos
    sort(resultado.begin(), resultado.end());
    //resultado.resize(8);

        //Elimino las direcciones repetidas.
    for (int i=0; i<(int)resultado.size()-1; i++){
        Vect vectorNodo(malla->getNodo(indNodo)->getPunto());
        Nodo* nodoOpuesto=malla->getNodo(resultado[i].indnodo);
        Vect vectorNodoOpuesto(nodoOpuesto->getPunto());
        Vect vectorArco=vectorNodoOpuesto-vectorNodo;
        vectorArco.normalizar();
        for (int j=i+1; j<(int)resultado.size(); j++){
            Nodo* nodoOpuestoj=malla->getNodo(resultado[j].indnodo);
            Vect vectorNodoOpuestoj(nodoOpuestoj->getPunto());
            Vect vectorArcoj=vectorNodoOpuestoj-vectorNodo;
            vectorArcoj.normalizar();
            if (vectorArco.prodPunto(vectorArcoj)>0.95 && vectorArco.prodPunto(vectorArcoj)<1.05)
                resultado.erase(resultado.begin()+j);
            }
        }

    //Les agregamos sus ponderaciones de acuerdo a su ubicacion.
    //Obtenemos el centro de gravedad.
    /*double centrogx=0,centrogy=0,centrogz=0;
    for (int i=0; i<(int)resultado.size(); i++){
        centrogx+=malla->getNodo(resultado[i].indnodo)->getPunto().getX();
        centrogy+=malla->getNodo(resultado[i].indnodo)->getPunto().getY();
        centrogz+=malla->getNodo(resultado[i].indnodo)->getPunto().getZ();
        }
    centrogx=centrogx/resultado.size();
    centrogy=centrogy/resultado.size();
    centrogz=centrogz/resultado.size();*/

    //De acuerdo a la distancia al cg asignamos la ponderacion.
    for (int i=0; i<(int)resultado.size(); i++){
        /*Vect vectorNodo(centrogx,centrogy,centrogz);
        Nodo* nodoOpuesto=malla->getNodo(resultado[i].indnodo);
        Vect vectorNodoOpuesto(nodoOpuesto->getPunto());
        Vect vectorArco=vectorNodoOpuesto-vectorNodo;
        double distancia=vectorArco.largo();
        resultado[i].ponderacionubicacion=distancia;*/

        Vect vectorNodo(malla->getNodo(indNodo)->getPunto());
        Nodo* nodoOpuesto=malla->getNodo(resultado[i].indnodo);
        Vect vectorNodoOpuesto(nodoOpuesto->getPunto());
        Vect vectorArco=vectorNodoOpuesto-vectorNodo;
        double distancia=vectorArco.largo();
        resultado[i].ponderacionubicacion=1/distancia;
        }

    if (indNodo==5000){
        malla->setNodoDestacado(indNodo);
        for (int i=0;i<(int)resultado.size();i++)
            malla->setNodoDestacado(resultado[i].indnodo);
        }

    return resultado;
    }

void DistribuirHormona::paseoHormonas(){
    //Reseteamos las concentraciones antiguas
    for (int i=0; i<=malla->getMaxIndiceNodos(); i++){
        Nodo* nodo=malla->getNodo(i);
        if (nodo!=NULL)
            nodo->setConcentracion(0);
        }

    //Calculamos las nuevas concentraciones mediante paseos al azar.
    int npaseos=1000;
    for (int i=0; i<=malla->getMaxIndiceNodos(); i++){
        Nodo* nodo=malla->getNodo(i);
        if (nodo!=NULL && malla->esNodoBordeSuperior(i)){
            for (int ipaseo=0; ipaseo<npaseos; ipaseo++){
                int indNodoPaseo=i;
                while (true){
                    Nodo* nodoPaseo=malla->getNodo(indNodoPaseo);
                    nodoPaseo->setConcentracion(nodoPaseo->getConcentracion()+1.0);
                    if (malla->esNodoBordeInferior(indNodoPaseo)) break;
                    indNodoPaseo=paseoAlAzar(indNodoPaseo);
                    }
                //break;
                }
            //break;
            }
        }

    //Normalizo las concentraciones.
    double maxconcentracion=0;
    for (int i=0; i<=malla->getMaxIndiceNodos(); i++){
        Nodo* nodo=malla->getNodo(i);
        if (nodo!=NULL && nodo->getConcentracion()>maxconcentracion)
            maxconcentracion=nodo->getConcentracion();
        }
    for (int i=0; i<=malla->getMaxIndiceNodos(); i++){
        Nodo* nodo=malla->getNodo(i);
        if (nodo!=NULL)
            nodo->setConcentracion(0.5+0.5*(nodo->getConcentracion()/maxconcentracion));
        }
    malla->setConcentracionMin(0.0);
    malla->setConcentracionMax(1.0);
    }

int DistribuirHormona::paseoAlAzar(int indNodo){
    vector<NodoProb> nodoprob=nodosprob[indNodo];

    //vector<double> probabilidades=nodo->getProbabilidadArcos();
    int i;
    double limiteinferior=0;
    double limitesuperior=nodoprob[0].probabilidad;
    //srand( time(NULL) );
    double azar=1.0*rand()/RAND_MAX;

    for (i=0; i<(int)nodoprob.size(); i++){

        if (azar>=limiteinferior && azar<=limitesuperior)
            break;

        limiteinferior=limitesuperior;
        if (i+1>=(int)nodoprob.size())
            limitesuperior=1;
        else
            limitesuperior=limitesuperior+nodoprob[i+1].probabilidad;
        }

    //int indArcoSeleccionado=nodo->getArcos()[i];
    //int indNodoSeleccionado=malla->getArco(indArcoSeleccionado)->getNodoDistinto(indNodo);
    int indNodoSeleccionado=nodoprob[i].indnodo;

    return indNodoSeleccionado;
    }

double DistribuirHormona::calcularProbabilidad(int indNodo, int indNodoDestino, double ponderacion){
    assert(indNodo!=indNodoDestino);

    //Calculo el vector del arco.
    Nodo* nodo=malla->getNodo(indNodo);
    Vect vectorNodo(nodo->getPunto());
    Nodo* nodoOpuesto=malla->getNodo(indNodoDestino);
    Vect vectorNodoOpuesto(nodoOpuesto->getPunto());
    Vect vectorArco=vectorNodoOpuesto-vectorNodo;
    vectorArco.normalizar();

    //Obtengo el vector gravedad
    Vect vectorGravedad=Vect(0,-1,0);

    //Obtengo el vector longitudinal
    Vect vectorLongitudinal=getVectorLongitudinal(nodo->getPunto().getY());

    //Calculo el vector tangencial
    Vect vectorTangencial=vectorLongitudinal.prodCruz(nodo->getNormal());
    //Vect *vectorTangencial=new Vect(1,0,0);

    //Proyecto los vectores sobre el vector arco
    double proyeccionGravedad=vectorGravedad.prodPunto(vectorArco);
    double proyeccionTangencial=fabs(vectorTangencial.prodPunto(vectorArco));
    double proyeccionLongitudinal=vectorLongitudinal.prodPunto(vectorArco);

    double probabilidadArco=factorgravitacional*proyeccionGravedad+
                            factorlongitudinal*proyeccionLongitudinal+
                            factortangencial*proyeccionTangencial;

    probabilidadArco=probabilidadArco*ponderacion;

    if(probabilidadArco<0)
        probabilidadArco=0;

    return probabilidadArco;
    }


Vect DistribuirHormona::getVectorLongitudinal(double altura){
    vector<Punto> medula=malla->getMedula();

    int i;
    for (i=0; i+1<(int)medula.size()-1; i++){
        if (altura<=medula[i+1].getY())
            break;
        }
    int sector=i;

    Vect v1(medula[sector].getX(),medula[sector].getY(),medula[sector].getZ());
    Vect v2(medula[sector+1].getX(),medula[sector+1].getY(),medula[sector+1].getZ());
    Vect vectorLongitudinal=v1-v2;
    vectorLongitudinal.normalizar();

    return vectorLongitudinal;
    }


DistribuirHormona::~DistribuirHormona()
{
    delete []nodosprob;
}


