#include "delaunaylongestedgebisection.h"
#include "mallatriangulos.h"

void DelaunayLongestEdgeBisection::aplicar(Malla *malla, Criterio *criterio){
    for(int i=0; i<=malla->getMaxIndiceCaras(); i++) {
        if(malla->getCara(i)!=NULL && !criterio->seCumple(malla,i)) {
            cout << "La cara(" << i << ") es mala" << endl;
            refine(malla,criterio,i);
            i = 0;
        	}
		}
	}

void DelaunayLongestEdgeBisection::refine(Malla *malla, Criterio* criterio, int ind_cara){
	//@todo: poner assert que compruebe que la malla es de triángulos
	MallaTriangulos *malla_t = (MallaTriangulos *)malla;
	int ind_arco=malla_t->getCara(ind_cara)->getArcoMasLargo(malla_t);
	malla_t->makeDelaunay(ind_arco);

	if(!criterio->seCumple(malla,ind_cara))
        //debemos dividir el arco, agregando un punto al centro.
        vector<int> nuevos_arcos = malla_t->edgeSplit(ind_arco,0.5);
	}
