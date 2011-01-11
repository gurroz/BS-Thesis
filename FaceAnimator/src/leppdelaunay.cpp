#include "leppdelaunay.h"
#include "lepp.h"
#include "mallatriangulos.h"

void LeppDelaunay::aplicar(Malla *malla, Criterio *criterio){
    assert(malla->checkMalla(true) >= 0);
    bool seEncontroInterseccion=true;
	while(seEncontroInterseccion==true){
		seEncontroInterseccion=false;
    	for(int i=0; i<=malla->getMaxIndiceCaras(); i++) {
    	    if(malla->getCara(i)!=NULL && !criterio->seCumple(malla,i)) {
    	        cout << "Aplicando Refinamiento a cara " << i << " de " << (malla->getMaxIndiceCaras()+1) << " (" << (float)i/(malla->getMaxIndiceCaras()+1)*100 << "%)" <<endl;
    	        Improve(malla,i);
				seEncontroInterseccion=true;
    	    	}
			}
		}
    assert(malla->checkMalla(true) >= 0);
	}

void LeppDelaunay::BoundaryEdgePointInsertion(Malla *malla, int ind_arco){
	//@todo: agregar assert que verifique que la malla es de triángulos
	MallaTriangulos *malla_t = (MallaTriangulos *)malla;

	//Obtenemos los indices de los arcos que comparten la misma cara que ind_arco
    int ind_a1 = -1;
    int ind_a2 = -1;

    // Indices de las caras, una de las 2 es distinta de -1.
    int ind_c1 = malla_t->getArco(ind_arco)->getCara1();
    int ind_c2 = malla_t->getArco(ind_arco)->getCara2();
    //Indices de los nodos
    int ind_p1 = malla_t->getArco(ind_arco)->getNodo1();
    int ind_p2 = malla_t->getArco(ind_arco)->getNodo2();
    if(ind_c1 != -1) {
        ind_a1 = malla_t->getArcoOpuestoNodo(ind_c1,ind_p1);
        ind_a2 = malla_t->getArcoOpuestoNodo(ind_c1,ind_p2);
    	}
    if(ind_c2 != -1) {
        ind_a1 = malla_t->getArcoOpuestoNodo(ind_c2,ind_p1);
        ind_a2 = malla_t->getArcoOpuestoNodo(ind_c2,ind_p2);
    	}

    //Operacion B1: refinamos el arco en el medio.
    vector<int> nuevos_arcos = malla_t->edgeSplit(ind_arco,0.5);

    //Operacion B2: Local edge swapping of the Malla malla to produce a CDT
    //Los arco en que se podria hacer flip para cumplir CTD son ind_a1 y ind_a2
    malla_t->makeDelaunay(ind_a1);
    malla_t->makeDelaunay(ind_a2);
	}

void LeppDelaunay::TerminalEdgePointInsertion(Malla *malla, int ind_arco){
	//@todo: agregar assert que verifique que la malla es de triángulos
	MallaTriangulos *malla_t = (MallaTriangulos *)malla;

	//Obtenemos los indices de los arcos que comparten las mismas caras que ind_arco
    int ind_a1_c1, ind_a2_c1, ind_a1_c2, ind_a2_c2;

    // Indices de las caras que separa ind_arco.
    int ind_c1 = malla_t->getArco(ind_arco)->getCara1();
    int ind_c2 = malla_t->getArco(ind_arco)->getCara2();
    //Indices de los nodos que forman ind_arco
    int ind_p1 = malla_t->getArco(ind_arco)->getNodo1();
    int ind_p2 = malla_t->getArco(ind_arco)->getNodo2();

    ind_a1_c1 = malla_t->getArcoOpuestoNodo(ind_c1,ind_p1);
    ind_a2_c1 = malla_t->getArcoOpuestoNodo(ind_c1,ind_p2);
    ind_a1_c2 = malla_t->getArcoOpuestoNodo(ind_c2,ind_p1);
    ind_a2_c2 = malla_t->getArcoOpuestoNodo(ind_c2,ind_p2);


    //Operacion T1: refinamos el arco en el medio.
    vector<int> nuevos_arcos = malla_t->edgeSplit(ind_arco,0.5);

    //Operacion T2: Local edge swapping of the Malla malla to produce a CDT
    malla_t->makeDelaunay(ind_a1_c1);
    malla_t->makeDelaunay(ind_a2_c1);
    malla_t->makeDelaunay(ind_a1_c2);
    malla_t->makeDelaunay(ind_a2_c2);
	}

void LeppDelaunay::PointInsertion(Malla *malla, int ind_cara){
	Lepp objetoLepp;
	vector<int> leep = objetoLepp.findLepp(malla, ind_cara);
    int arco_terminal = malla->getCara(leep[leep.size()-1])->getArcoMasLargo(malla);

    // Find the first  boundary triangle t*, non equal to t, in LEEP(t), with boundary edge L_b not equal to the smallest edge of t*.
    int boundary_t = -1;
    int boundary_edge = -1;
    for(int i=1; i<(int)leep.size(); i++) {
        if(malla->esCaraBorde(leep[i])) {
            vector<int> arcos_borde = malla->getArcosBordeCara(leep[i]);
            //Recorro todos los arcos borde y veo si encuentro alguno distinto al arco mas corto
            for(int j=0; j<(int)arcos_borde.size(); j++) {
                if(arcos_borde[j] != malla->getCara(leep[i])->getArcoMasCorto(malla)) {
                    boundary_t = leep[i];
                    boundary_edge = arcos_borde[j];
                    //Salimos
                    j = arcos_borde.size();
                }
            }
        }
        //si ya encontramos boundary_t salimos
        if(boundary_edge != -1) {
            i = leep.size();
        }
    }

    if(boundary_edge != -1)
        BoundaryEdgePointInsertion(malla, boundary_edge);
    else
        TerminalEdgePointInsertion(malla, arco_terminal);

	}

void LeppDelaunay::Improve(Malla *malla, int ind_cara){
	Cara *bad_cara = malla->getCara(ind_cara);
    Cara *new_cara = malla->getCara(ind_cara);
    while(bad_cara == new_cara) { //while bad_cara remains without being modified DO
        bool condicion = false; // if t is a boundary triangle with one boundary edge L_b noy equal to the smallest edge of t.
        int boundary_edge = -1;
        if(malla->esCaraBorde(ind_cara)) {
            vector<int> arcos_borde = malla->getArcosBordeCara(ind_cara);
            //Recorro todos los arcos borde y veo si encuentro alguno distinto al arco mas corto
            for(int i=0; i<(int)arcos_borde.size(); i++) {
                if(arcos_borde[i] != malla->getCara(ind_cara)->getArcoMasCorto(malla)) {
                    condicion = true;
                    boundary_edge = arcos_borde[i];
                	}
            	}
        	}

        if(condicion)
            BoundaryEdgePointInsertion(malla,boundary_edge);
        else
            PointInsertion(malla,ind_cara);

        //actualizamos new_cara.
        new_cara = malla->getCara(ind_cara);
    	}
	}
