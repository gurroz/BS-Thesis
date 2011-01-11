#include "almacenatoxyzu.h"

#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>

AlmacenaToXYZU::AlmacenaToXYZU():AlgAlmacenamiento(){

	}


void AlmacenaToXYZU::aplicar(Malla *malla, string filename){
	//Lineas necesarias para que scanf lea archivo en computadores seteados en otro lenguaje.
	setlocale(LC_NUMERIC, "POSIX");

	int posextension=filename.rfind(".");
	string nombrefile=filename.substr(0,posextension);
	string extension=filename.substr(posextension+1,filename.length());

	if (posextension==0){
		nombrefile=filename;
		extension="txt";
		}


	stringstream archivox;
	stringstream archivoy;
	stringstream archivoz;
	stringstream archivou;

	archivox << nombrefile << "_nx." << extension;
	archivoy << nombrefile << "_ny." << extension;
	archivoz << nombrefile << "_nz." << extension;
	archivou << nombrefile << "_u." << extension;

	FILE *archivo_x = fopen(archivox.str().c_str(),"w");
	FILE *archivo_y = fopen(archivoy.str().c_str(),"w");
	FILE *archivo_z = fopen(archivoz.str().c_str(),"w");
	FILE *archivo_u = fopen(archivou.str().c_str(),"w");

	char separador1[32] = "% Coordinates\n";
    fprintf(archivo_x,"%s",separador1);
    fprintf(archivo_y,"%s",separador1);
    fprintf(archivo_z,"%s",separador1);
    fprintf(archivo_u,"%s",separador1);

    Nodo *nodo;
	int* nuevoIndiceNodos=new int[malla->getMaxIndiceNodos()+1];
	int nlinea=0;
    for(int i=0; i<=malla->getMaxIndiceNodos(); i++) {
        nodo = malla->getNodo(i);
        if(nodo != NULL) {
            fprintf(archivo_x,"%f   %f  %f\n",nodo->getPunto().getX(),nodo->getPunto().getY(),nodo->getPunto().getZ());
            fprintf(archivo_y,"%f   %f  %f\n",nodo->getPunto().getX(),nodo->getPunto().getY(),nodo->getPunto().getZ());
            fprintf(archivo_z,"%f   %f  %f\n",nodo->getPunto().getX(),nodo->getPunto().getY(),nodo->getPunto().getZ());
            fprintf(archivo_u,"%f   %f  %f\n",nodo->getPunto().getX(),nodo->getPunto().getY(),nodo->getPunto().getZ());
        	nuevoIndiceNodos[i]=nlinea;
			nlinea++;
		}
    }

    ostringstream myStream;
    myStream << "% Elements (" << malla->getTipoMalla() << ")\n";
    string str_separador2 = myStream.str();
    const char *separador2 = str_separador2.c_str();

    fprintf(archivo_x,"%s",separador2);
    fprintf(archivo_y,"%s",separador2);
    fprintf(archivo_z,"%s",separador2);
    fprintf(archivo_u,"%s",separador2);

    Cara *c;
    vector<int> ind_nodos;
    for(int i=0; i<=malla->getMaxIndiceCaras(); i++) {
        c = malla->getCara(i);
        if(c != 0) {
            ind_nodos = c->getNodos();
            for(int j=0; j < c->getNumElem();++j) {
                char *delimitador = "  ";
                if(j == c->getNumElem() -1)
                    delimitador = "\n";
                fprintf(archivo_x,"%d%s",nuevoIndiceNodos[ind_nodos[j]]+1,delimitador);
                fprintf(archivo_y,"%d%s",nuevoIndiceNodos[ind_nodos[j]]+1,delimitador);
                fprintf(archivo_z,"%d%s",nuevoIndiceNodos[ind_nodos[j]]+1,delimitador);
                fprintf(archivo_u,"%d%s",nuevoIndiceNodos[ind_nodos[j]]+1,delimitador);
            }
        }
    }

    char separador_x[32] = "% Data (nx)\n";
    char separador_y[32] = "% Data (ny)\n";
    char separador_z[32] = "% Data (nz)\n";
    char separador_u[32] = "% Data (u)\n";

    fprintf(archivo_x,"%s",separador_x);
    fprintf(archivo_y,"%s",separador_y);
    fprintf(archivo_z,"%s",separador_z);
    fprintf(archivo_u,"%s",separador_u);

    for(int i=0; i<=malla->getMaxIndiceNodos(); i++) {
        nodo = malla->getNodo(i);
        if(nodo != NULL) {
            fprintf(archivo_x,"%f\n",nodo->getNormal().getPunto().getX());
            fprintf(archivo_y,"%f\n",nodo->getNormal().getPunto().getY());
            fprintf(archivo_z,"%f\n",nodo->getNormal().getPunto().getZ());
            fprintf(archivo_u,"%f\n",nodo->getConcentracion());
        }
    }

	delete nuevoIndiceNodos;

    fclose(archivo_x);
    fclose(archivo_y);
    fclose(archivo_z);
    fclose(archivo_u);

	setlocale(LC_NUMERIC, "");
	}
