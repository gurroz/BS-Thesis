#include "verificacionnodosvecinos.h"
#include "mallatriangulos.h"

#include "adaptercomputationalgeometry.h"

VerificacionNodosVecinos::VerificacionNodosVecinos(double val):AlgDesplazamientoMallaTriangulos(){
	this->val=val;
	this->nnodosborrados=0;
	}

void VerificacionNodosVecinos::aplicar(Malla *malla){
	int ninconsistencias=repairMalla(malla);
	double mov=moverHasta(malla);
	cout << "Total de inconsistencias encontradas=" << ninconsistencias << endl;
	cout << "Total de trayectorias reparadas=" << ninconsistencias-nnodosborrados << endl;
	cout << "Total de nodos borrados=" << nnodosborrados << endl;
	cout << "Malla movida una proporcion = " << mov << endl;
	assert(malla->checkMalla(true) >= 0);
	}

int VerificacionNodosVecinos::repairMalla(Malla *malla){
	//recorremos los nodos de la malla buscando donde se van a producir inconsistencias.
	int ninconsistencias=0;
	malla->clearNodosDestacados();
    for(int indNodo=0; indNodo<=malla->getMaxIndiceNodos(); indNodo++) {
			Nodo* nodoActual=malla->getNodo(indNodo);
			if (nodoActual!=NULL) {
				bool seIntersecta=checkInterseccionNodo(malla, indNodo);
				if (seIntersecta){
					ninconsistencias++;
					//nodosInconsistentes.push_back(indNodo);
					corrigeInconsistencia(malla, indNodo);
					}
				}
			}

	return ninconsistencias;
	}

double VerificacionNodosVecinos::moverHasta(Malla* malla){
	//Ahora movemos la malla.
	malla->moverNodosSegunConcentracion(val);
	return val;
	}

bool VerificacionNodosVecinos::checkInterseccionNodo(Malla* malla, int indNodo){
	assert(malla->getNodo(indNodo)!=NULL);

			Nodo* nodoActual=malla->getNodo(indNodo);

			//Definimos los puntos que componen el segmento de proyeccion del nodo.
			Punto PuntoProyecNodoActual=  Punto(	nodoActual->getPunto().getX()+nodoActual->getNormal().getPunto().getX()*val*nodoActual->getConcentracion(),
													nodoActual->getPunto().getY()+nodoActual->getNormal().getPunto().getY()*val*nodoActual->getConcentracion(),
													nodoActual->getPunto().getZ()+nodoActual->getNormal().getPunto().getZ()*val*nodoActual->getConcentracion());
			Vect q=Vect(nodoActual->getPunto());
			Vect r=Vect(PuntoProyecNodoActual);

			if(q == r) // El nodo actual no se desplaza
                return false;

			//Revisamos cada una de las caras vecinas al nodo.
			vector<int> indCarasVecinas=nodoActual->getCaras();
			for (int indCara=0; indCara<(int)indCarasVecinas.size(); indCara++){
				Cara* caraVecina=malla->getCara(indCarasVecinas[indCara]);
				vector<int> puntos=caraVecina->getPuntosDistintos(indNodo);

				//Formar paredes del cilindro que rodea la proyeccion (una por cada arco (de la cara) no incidente en indNodo)
				for (int j=0; j<caraVecina->getNumElem()-2;++j) {
                    int indPuntoA=puntos[j];
                    int indPuntoB=puntos[j+1];
                    Nodo* NodoA=malla->getNodo(indPuntoA);
                    Nodo* NodoB=malla->getNodo(indPuntoB);
                    Punto PuntoProyecA=Punto(NodoA->getPunto().getX()+NodoA->getNormal().getPunto().getX()*val*NodoA->getConcentracion(),
                                             NodoA->getPunto().getY()+NodoA->getNormal().getPunto().getY()*val*NodoA->getConcentracion(),
                                             NodoA->getPunto().getZ()+NodoA->getNormal().getPunto().getZ()*val*NodoA->getConcentracion());
                    Punto PuntoProyecB=Punto(NodoB->getPunto().getX()+NodoB->getNormal().getPunto().getX()*val*NodoB->getConcentracion(),
                                             NodoB->getPunto().getY()+NodoB->getNormal().getPunto().getY()*val*NodoB->getConcentracion(),
                                             NodoB->getPunto().getZ()+NodoB->getNormal().getPunto().getZ()*val*NodoB->getConcentracion());

                    AdapterComputationalGeometry adapter;
                    char resultadoInterseccion;

                    if(PuntoProyecA != NodoA->getPunto()) { // Si A se desplaza

                        //Chequeamos interseccion con el primer triangulo
                        Vect triangulo1[3];
                        triangulo1[0]=Vect(NodoA->getPunto());
                        triangulo1[1]=Vect(PuntoProyecA);
                        triangulo1[2]=Vect(PuntoProyecB);
                        Vect qpoints(q.getPunto());
                        Vect rpoints(r.getPunto());

                        resultadoInterseccion=adapter.SegTriInt(triangulo1,qpoints,rpoints);

                        if (resultadoInterseccion!='0'){
                            return true;
                            }
                    }

                    if(PuntoProyecB != NodoB->getPunto()) { // Si B se desplaza

                        //Chequeamos interseccion con el segundo triangulo
                        Vect triangulo2[3];
                        triangulo2[0]=Vect(NodoB->getPunto());
                        triangulo2[1]=Vect(NodoA->getPunto());
                        triangulo2[2]=Vect(PuntoProyecB);
                        Vect q2points(q.getPunto());
                        Vect r2points(r.getPunto());

                        resultadoInterseccion=adapter.SegTriInt(triangulo2,q2points,r2points);

                        if (resultadoInterseccion!='0'){
                            return true;
                            }
                        }
                    }
				}

	return false;
	}

bool VerificacionNodosVecinos::corrigeInconsistencia (Malla *malla, int indNodo){
	assert(malla->getNodo(indNodo)!=NULL);

	Nodo* nodo=malla->getNodo(indNodo);
	Vect viejaNormal=nodo->getNormal();
	Vect nuevaNormal;
	vector<int> indArcosVecinos=nodo->getArcos();
	for (int indArco=0; indArco< (int)indArcosVecinos.size(); indArco++){
		Arco* arcoVecino=malla->getArco(indArcosVecinos[indArco]);
		int indPuntoA=arcoVecino->getNodoDistinto(indNodo);
		Nodo* NodoA=malla->getNodo(indPuntoA);
		Vect vectorVecino=NodoA->getNormal()*(val*NodoA->getConcentracion());
		nuevaNormal=nuevaNormal+vectorVecino;
		}
	//Normalizamos.
	nuevaNormal = nuevaNormal*(1/nuevaNormal.largo());
	nodo->setNormal(nuevaNormal);
	//Si la inconsistencia no se corrige, borramos el nodo central.
	if (checkInterseccionNodo(malla,indNodo)==true){
		nodo->setNormal(viejaNormal);
		nnodosborrados++;
		borrarNodoCentral(malla,indNodo);
		return false;
		}
	return true;
	}

void VerificacionNodosVecinos::borrarNodoCentral(Malla* malla, int indNodo){
	assert(malla->getNodo(indNodo)!=NULL);
	//@todo: agregar assert que verifique que la malla es de triángulos
	MallaTriangulos *malla_t = (MallaTriangulos *)malla;

	Nodo* nodo=malla_t->getNodo(indNodo);
	vector<int> arcos_nodo = nodo->getArcos();

    for(int i=0; i<(int)arcos_nodo.size(); i++) {
		int resultado=malla_t->vertexDeletion(arcos_nodo[i],indNodo);
        if(resultado!=-1) {
        	break;
            }
		}

	}
