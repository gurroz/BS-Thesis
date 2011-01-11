#ifndef MALLATRIANGULOS_H
#define MALLATRIANGULOS_H

#include "malla.h"
#include "mallacuadrilateros.h"
#include "triangulo.h"
#include "algcentrotriangulo.h"

class MallaCuadrilateros;

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz, Cristina Melo
Esta clase representa una malla, la cual esta compuesta por Nodos, Arcos y Caras.
 */
class MallaTriangulos : public Malla {
    public:
        // construtores:
        MallaTriangulos(Nodos *nds, Arcos *arcs, Caras *crs); // Malla con esos Nodos, Arcos y Caras.
        MallaTriangulos(Punto p0, Punto p1, Punto p2); // Malla que contiene 1 triángulo (3 Nodos, 3 Arcos y 1 Cara);
        MallaTriangulos(Punto p0, Punto p1, Punto pc0, Punto pc1); // Malla que contiene 2 triángulo contigüos (4 Nodos, 5 Arcos y 2 Cara);

		// transformaciones
        int edgeFlip(int ind_arco); // realiza un flip o swap, retorna el índice del nuevo arco
        vector<int> edgeSplit(int ind_arco, double dist, int retorna=0); // inserta un punto en ind_arco a una distancia dist desde el primer punto del arco. dist debe ser entre 0 y 1. Por ejemplo si dist=0.5 inserta un punto en la mitad del arco. Retorna los indices de los nuevos arcos agregados a la malla. Retorna=0, por defecto retorna los nuevos arcos. Retorna=1, retorna las nuevas caras. Retorna=2, retorna el nuevo nodo.
        int edgeCollapse(int ind_arco, double dist); // reduce el arco a un punto. dist es para ver en que parte del arco queda el punto. Por ejemplo si dist=0.5 el punto queda en la mitad del arco.
        int vertexDeletion(int indArcoAColapsar, int indVerticeABorrar);	//Metodo que sustituira a edgeCollapse. Colapsa un Arco eliminando un vertice.
		int edgeCollapse2(int ind_arco, double dist);	//Reimplementacion de EdgeCollapse.
        virtual int colapsarRegion(int indVerticeCentral);	//Colapsa una region en un nodo
		MallaCuadrilateros* cuadrangular(AlgCentroTriangulo *alg_centro_triangulo);

		// métodos Delaunay
		int isDelaunay(int ind_arco);	//Indica si el arco es Delaunay
		void makeDelaunay(int ind_arco);	//Aplica Delaunay al arco. Este metodo chequea antes si el arco es Delaunay.

        // métodos dirigidos al desplazamiento de la malla:
        void manejaInconsitenciaArco(int ind_arco);
        void manejaInconsistenciaArcoAntes(int ind_arco, double val);

        virtual FabricaAlgoritmos *getFabricaAlgoritmos(); // crea una fábrica de algoritmos para mallas de cuadriláteros, si no existe, o retorna la existente

		//Destructor
		~MallaTriangulos() {};

};

#endif
