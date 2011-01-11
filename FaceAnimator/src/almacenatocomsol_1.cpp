#include "almacenatocomsol_1.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>

AlmacenaToComsol_1::AlmacenaToComsol_1():AlgAlmacenamiento(){

	}


void AlmacenaToComsol_1::aplicar(Malla *malla, string filename){
	//Lineas necesarias para que scanf lea archivo en computadores seteados en otro lenguaje.
	setlocale(LC_NUMERIC, "POSIX");

	FILE *archivo_x = fopen(filename.c_str(),"w");

	char separador1[32] = "% Coordinates\n";
    fprintf(archivo_x,"%s",separador1);

    Nodo *nodo;
	int* nuevoIndiceNodos=new int[malla->getMaxIndiceNodos()+1];
	int nlinea=0;
    for(int i=0; i<=malla->getMaxIndiceNodos(); i++) {
        nodo = malla->getNodo(i);
        if(nodo != NULL) {
            fprintf(archivo_x,"%f   %f  %f\n",nodo->getPunto().getX(),nodo->getPunto().getY(),nodo->getPunto().getZ());
        	nuevoIndiceNodos[i]=nlinea;
			nlinea++;
		}
    }

    ostringstream myStream;
    myStream << "% Elements (" << malla->getTipoMalla() << ")\n";
    string str_separador2 = myStream.str();
    const char *separador2 = str_separador2.c_str();

    fprintf(archivo_x,"%s",separador2);

    Cara *c;
    vector<int> ind_nodos;
    for(int i=0; i<=malla->getMaxIndiceCaras(); i++) {
        c = malla->getCara(i);
        if(c != 0) {
            ind_nodos = c->getNodos();
			//Nota: Se invierte el orden de insercion de los puntos, para que las normales queden seteadas correctamente.
			//ya que en el archivo cms_1 los nodos estan al reves, dejando las normales hacia adentro.
            //for(int j=c->getNumElem()-1; j>=0 ;--j) { // Por bug archivos de entrada
            for(int j=0; j<c->getNumElem(); ++j) { // así debiera ser
                char *delimitador = "  ";
                //if(j == 0) // Por bug archivos de entrada
                if(j == c->getNumElem()-1) // así debiera ser
                    delimitador = "\n";
                fprintf(archivo_x,"%d%s",nuevoIndiceNodos[ind_nodos[j]]+1,delimitador);
            }
        }
    }

	delete nuevoIndiceNodos;

    fclose(archivo_x);

	setlocale(LC_NUMERIC, "");
	}
