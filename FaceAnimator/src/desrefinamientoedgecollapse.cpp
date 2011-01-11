#include "desrefinamientoedgecollapse.h"
#include "mallatriangulos.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>


void DesrefinamientoEdgeCollapse::aplicar(Malla *malla, Criterio *criterio){
	bool seEncontroInterseccion=true;
	while(seEncontroInterseccion==true){
		seEncontroInterseccion=false;
    	for(int i=0; i<=malla->getMaxIndiceCaras(); i++) {
    	    if(malla->getCara(i)!=NULL && find(excluidos.begin(),excluidos.end(),i)==excluidos.end() && criterio->seCumple(malla,i)) {
    	        cout << "Aplicando Desrefinamiento a cara " << i << " de " << (malla->getMaxIndiceCaras()+1) << " (" << (float)i/(malla->getMaxIndiceCaras()+1)*100 << "%)" <<endl;
				desrefinar(malla,i);
    	        seEncontroInterseccion=true;
    	    	}
			}
		}
	}

int DesrefinamientoEdgeCollapse::desrefinar(Malla* malla, int indCara){
	//@todo: agregar assert que verifique que la malla es de triángulos
	MallaTriangulos *malla_t = (MallaTriangulos *)malla;
	int arcomascorto=malla_t->getCara(indCara)->getArcoMasCorto(malla_t);
	int resultado=malla_t->edgeCollapse2(arcomascorto,0.5);
	if (resultado==-1)
		excluidos.push_back(indCara);

	return resultado;
	}
