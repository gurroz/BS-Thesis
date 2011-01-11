#include "almacenatomlldebug.h"
#include <stdio.h>

AlmacenaToMllDebug::AlmacenaToMllDebug():AlgAlmacenamiento(){

	}

void AlmacenaToMllDebug::aplicar(Malla *malla, string filename){
	//Lineas necesarias para que scanf lea archivo en computadores seteados en otro lenguaje.
	setlocale(LC_NUMERIC, "POSIX");

	FILE *archivoSalida = fopen(filename.c_str(),"w");

	fprintf(archivoSalida,"MLL (Debug file)\n");

    fprintf(archivoSalida,"%d %d %d\n",malla->getMaxIndiceNodos()+1,malla->getMaxIndiceCaras()+1,malla->getMaxIndiceArcos()+1);
    fprintf(archivoSalida,"%d %d %d\n",malla->getNumNodos(),malla->getNumCaras(),malla->getNumArcos());

    Nodo *nodo;
    Vect normal;
    cout << "Recorriendo Nodos" << endl;
    for(int i=0; i<=malla->getMaxIndiceNodos(); i++) {
        nodo = malla->getNodo(i);
        if(nodo == 0) {
            fprintf(archivoSalida,"Nodo{%d}=Vacio \n",i);
        }
        else {
            fprintf(archivoSalida,"Nodo{%d}=(%f,%f,%f) ",i,nodo->getPunto().getX(),nodo->getPunto().getY(),nodo->getPunto().getZ());

            vector<int> caras = nodo->getCaras();
            vector<int> arcos = nodo->getArcos();
            fprintf(archivoSalida,"Caras{");
            for(int j=0; j<(int)caras.size(); j++) {
                fprintf(archivoSalida,"%d",caras[j]);
                if(j<(int)caras.size()-1) {
                    fprintf(archivoSalida,",");
                }
            }
            fprintf(archivoSalida,"} Arcos{");
            for(int j=0; j<(int)arcos.size(); j++) {
                fprintf(archivoSalida,"%d",arcos[j]);
                if(j<(int)arcos.size()-1) {
                    fprintf(archivoSalida,",");
                }
            }
            fprintf(archivoSalida,"} ");
            normal = malla->getNodo(i)->getNormal();
            fprintf(archivoSalida,"Normal=(%f,%f,%f) ",normal.getPunto().getX(),normal.getPunto().getY(),normal.getPunto().getZ());
            fprintf(archivoSalida,"Concentracion={%f}",nodo->getConcentracion());
            fprintf(archivoSalida,"\n");
        }
    }
    cout << "Pasamos nodos" << endl;
    Arco *a;
    for(int i=0; i<=malla->getMaxIndiceArcos(); i++) {
        a = malla->getArco(i);
        //si se elimino un arco, puede que en esa posicion exista un puntero igual a 0, por eso nos aseguramos que el arco sea distinto de 0.
        if(a == 0) {
            fprintf(archivoSalida,"Arco{%d} Vacio\n",i);
        }
        else {
            fprintf(archivoSalida,"Arco{%d} Nodos{%d,%d} Caras{%d,%d}\n",i,a->getNodo1(),a->getNodo2(),a->getCara1(),a->getCara2());
        }
    }

    Cara *c;
    vector<int> ind_nodos;
    vector<int> ind_arcos;
    for(int i=0; i<=malla->getMaxIndiceCaras(); i++) {
        c = malla->getCara(i);
        //si se elimino una cara, puede que en esa posicion exista un puntero igual a 0, por eso nos aseguramos que la cara sea distinta de 0.
        if(c == 0) {
            fprintf(archivoSalida,"Cara{%d} Vacia\n",i);
        }
        else {
            ind_nodos = c->getNodos();
            ind_arcos = c->getArcos();
            fprintf(archivoSalida,"Cara{%d} %d ",i,c->getNumElem());
            fprintf(archivoSalida,"Nodos{");
            double conc_prom = 0;
            for(int j=0; j<(int)ind_nodos.size(); j++) {
                conc_prom = conc_prom + malla->getNodo(ind_nodos[j])->getConcentracion();
                fprintf(archivoSalida,"%d",ind_nodos[j]);
                if(j<(int)ind_nodos.size()-1) {
                    fprintf(archivoSalida,",");
                }
            }
            fprintf(archivoSalida,"} ");
            fprintf(archivoSalida,"Arcos{");
            for(int j=0; j<(int)ind_arcos.size(); j++) {
                if(malla->getArco(ind_arcos[j]) != 0) {
                    fprintf(archivoSalida,"%d:%d-->%d",ind_arcos[j],malla->getArco(ind_arcos[j])->getNodo1(),malla->getArco(ind_arcos[j])->getNodo2());
                    if(j<(int)ind_arcos.size()-1) {
                        fprintf(archivoSalida,",");
                    }
                }
            }
            fprintf(archivoSalida,"} ");
            Vect normal = c->getNormal(malla);
            fprintf(archivoSalida,"Normal=(%f,%f,%f) ",normal.getPunto().getX(),normal.getPunto().getY(),normal.getPunto().getZ());
            fprintf(archivoSalida,"Concentracion=%f",conc_prom);
            fprintf(archivoSalida,"\n");
        }
    }

    fclose(archivoSalida);

	setlocale(LC_NUMERIC, "");
	}
