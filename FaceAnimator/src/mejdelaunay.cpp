#include "mejdelaunay.h"
#include "mallatriangulos.h"

MejDelaunay::MejDelaunay():AlgMejoramientoMallaTriangulos() {

}

void MejDelaunay::aplicar(Malla *malla) {
	//@todo: agregar assert que verifique que la malla es de triángulos
	MallaTriangulos *malla_t = (MallaTriangulos *)malla;

    //Hacemos los flip en donde se pueda y se mejoren los angulos.
    for(int i=0; i<=malla_t->getMaxIndiceArcos(); i++){
		if (malla_t->getArco(i)!=NULL){
			cout << "Aplicando Mejoramiento Delaunay en arco " << i << endl;
        	malla_t->makeDelaunay(i);
			}
		}
	}
