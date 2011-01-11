#ifndef MALLACUADRILATEROS_H
#define MALLACUADRILATEROS_H

#include "malla.h"
#include "cuadrilatero.h"
#include "mallatriangulos.h"

class MallaTriangulos;

/**
@author Cristina Melo
Esta clase representa una malla de cuadriláteros, la cual esta compuesta por Nodos, Arcos y Caras.
 */
class MallaCuadrilateros : public Malla {
    public:
        // construtores:
        MallaCuadrilateros(Nodos *nds, Arcos *arcs, Caras *crs); // Malla con esos Nodos, Arcos y Caras.

		// transformaciones
        virtual int colapsarRegion(int indVerticeCentral);	//Colapsa una region en un nodo
		MallaTriangulos *triangular();

        virtual FabricaAlgoritmos *getFabricaAlgoritmos(); // crea una fábrica de algoritmos para mallas de cuadriláteros, si no existe, o retorna la existente

		//Destructor
		~MallaCuadrilateros() {};

};

#endif

