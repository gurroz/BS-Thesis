#include "almacenatooff.h"
#include <stdio.h>

AlmacenaToOff::AlmacenaToOff(){

	}

void AlmacenaToOff::aplicar(Malla *malla, string filename){
	//Lineas necesarias para que scanf lea archivo en computadores seteados en otro lenguaje.
	setlocale(LC_NUMERIC, "POSIX");

	FILE *archivoSalida = fopen(filename.c_str(),"w");
	fprintf(archivoSalida,"OFF\n");

    fprintf(archivoSalida,"%d %d %d\n",malla->getNumNodos(),malla->getNumCaras(),malla->getNumArcos());

    Nodo *nodo;
	int* nuevoIndiceNodos=new int[malla->getMaxIndiceNodos()+1];
	int nlinea=0;
    for(int i=0; i<=malla->getMaxIndiceNodos(); i++) {
        nodo = malla->getNodo(i);
        if(nodo != NULL) {
            fprintf(archivoSalida,"%f %f %f\n",nodo->getPunto().getX(),nodo->getPunto().getY(),nodo->getPunto().getZ());
        	nuevoIndiceNodos[i]=nlinea;
			nlinea++;
		}
    }

    Cara *c;
    vector<int> ind_nodos;
    vector<int> ind_arcos;
    for(int i=0; i<=malla->getMaxIndiceCaras(); i++) {
        c = malla->getCara(i);
        if(c != 0) {
            ind_nodos = c->getNodos();
            ind_arcos = c->getArcos();
            fprintf(archivoSalida,"%d ",c->getNumElem());
            double conc_prom = 0;
            for(int j=0; j<(int)ind_nodos.size(); j++) {
                conc_prom = conc_prom + malla->getNodo(ind_nodos[j])->getConcentracion();
                fprintf(archivoSalida,"%d ",nuevoIndiceNodos[ind_nodos[j]]);
            }
            fprintf(archivoSalida,"\n");
        }
    }

	delete nuevoIndiceNodos;

    fclose(archivoSalida);

	setlocale(LC_NUMERIC, "");
	}
