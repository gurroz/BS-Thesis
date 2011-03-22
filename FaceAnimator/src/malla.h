#ifndef MALLA_H
#define MALLA_H

#include <string>
#include <set>
#include <map>
#include <GL/gl.h>

#include "definiciones.h"

#include "nodo.h"
#include "nodos.h"
#include "arcos.h"
#include "arco.h"
#include "cara.h"
#include "caras.h"
#include "polinomio.h"
#include "fabricaalgoritmos.h"
#include "movimientosNodos.h"

class Arco;
class Arcos;
class Cara;
class Caras;
class FabricaAlgoritmos;

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz, Cristina Melo
Esta clase representa una malla, la cual esta compuesta por Nodos, Arcos y Caras.
 */
class Malla{
    protected:
        Nodos *nodos; // conjunto de nodos de la malla.
        Arcos *arcos; // conjunto de arcos de la malla.
        Caras *caras; // conjunto de caras de la malla.
        vector<Punto> medula;
        bool show_nodos_destacados; //indica si se deben destacar los nodos marcados como destacados.
		double concentracion_max; // indica la concentración máxima de los nodos de la malla.
        double concentracion_min; // indica la concentración mínima de los nodos de la malla.
		vector<int> nodosDestacados;	//Indica los indices de nodos que deben ser destacados en la visualizacion
		FabricaAlgoritmos* fabrica_algoritmos;
		GLuint textura;
		bool hasTextura;
		Malla *sgteMalla;
		MovimientosNodos *movimientos;

    public:
        // construtores:
        Malla(Punto p0, Punto p1); // Malla simple, contiene 2 Nodos y 1 Arco (0 caras).
        Malla(Nodos *nds, Arcos *arcs, Caras *crs); // Malla con esos Nodos, Arcos y Caras.
        Malla *nextMalla();
        void setNextMalla(Malla *m);

        // setters y getters:
		void setNodoDestacado(int indNodo);	//setea un nodo para ser destacado en la visualizacion
		void setMedula(vector<Punto> medula);
        void setConcentracionMax(double max);
        void setConcentracionMin(double min);
        void setConcentracionTodos(double val); // setea la concentración de cada nodo con valor val

		void setTextura(GLuint b);    //indica si la malla posee una textura asociada.
		GLuint getTextura();
		bool tieneTextura();
		void asignar_nodos_marcados(int *clos, int n);
		bool existeCaminoEntre(int n1, int n2);

        Nodos* getNodos();
        Nodo* getNodo(int ind_nodo); // get del nodo en ese indice.
        Arco* getArco(int ind_arco); // get del arco en ese indice.
        Cara* getCara(int ind_cara); // get de la cara en ese indice.
        int getMaxIndiceNodos(); // get del mayor índice de los nodos de la malla
        int getMaxIndiceArcos(); // get del mayor índice de los arcos de la malla
        int getMaxIndiceCaras(); // get del mayor índice de los caras de la malla
        int getNumNodos(); // get del número de nodos efectivos de la malla
        int getNumArcos(); // get del número de arcos efectivos de la malla
        int getNumCaras(); // get del número de caras efectivos de la malla
		void clearNodosDestacados();
		vector<int>* getNodosDestacados();
		vector<Punto> getMedula();
        double getConcentracionMax();
        double getConcentracionMin();
        virtual FabricaAlgoritmos *getFabricaAlgoritmos(); // crea una fábrica de algoritmos, según el tipo de malla, si no existe, o devuelve la existente
        void setMovimientos(string s);

        // métodos arcos:
        double getAnguloArco(int ind_arco); // retorna el angulo entre las caras que comparte el arco
        bool esArcoBorde(int ind_arco);
        bool esAnguloDiedro(int ind_arco, double anguloDiedroMax);	//Retorna true si el angulo diedro entre las dos caras que comparten el arco es mayor que anguloDiedroMax.
        bool esArcoConcavo(int ind_arco);
        bool esArcoFijo(int ind_arco); // Que sea fijo significa que no se puede realizar un flip sobre ese arco.

        // métodos nodos:
        bool esNodoBorde(int indNodo); //Indica si el nodo esta en un borde de la malla.
        bool esNodoBordeSuperior(int ind_nodo);
        bool esNodoBordeInferior(int ind_nodo);
        Vect calcularNormalNodo(int ind_nodo); // setea la normal de ese nodo.

        // métodos caras:
        double getAnguloCaras(int ind_cara1, int ind_cara2); // retorna el ángulo entre las caras
        bool sonCarasVecinas(int ind_cara1, int ind_cara2);
        bool esCaraBorde(int ind_cara);
        vector<int> getArcosBordeCara(int ind_cara);

        // transformaciones:
        void moverNodosSegunConcentracion(double val);
        void moverNodosSegunParametro(int ind, double val);
        void moverMallaModeloSegunAUV(int ind, double val);
        void moverNodosSegunShapeUnit(int ind, double val);

        virtual int colapsarRegion(int indVerticeCentral) {return -1;};	//Colapsa una region en un nodo

        // obtencion de indices:
        int getSiguienteCara(int indice, int ind_cara); // retorna la cara vecina de la cara ind_cara por el arco indice
        int getArcoOpuestoNodo(int ind_cara, int ind_nodo); // retorna el o los indice del o los arcos opuestos al nodo ind_nodo, en la cara ind_cara (Si la cara tiene 3 lados es un solo arco, asi que por el momento retorno solo un indice, despues se puede generalizar)
        int getNodoOpuestoNodo(int ind_cara, int ind_nodo); // retorna el o los indices del o los nodos opuestos al nodo ind_nodo por las cara ind_cara (Si la cara tiene 3 lados es un solo nodo, asi que por el momento retorno solo un indice, despues se puede generalizar)
        int getNodoOpuestoArco(int ind_cara, int ind_arco); // dado una cara y una arco de esa misma cara, retorna el nodo perteneciente a esa cara y que no pertenece a ese arco. (Si la cara tiene 3 lados es un solo nodo, asi que por el momento retorno solo un indice, despues se puede generalizar).
        int getCaraOpuestaNodo(int ind_cara, int ind_nodo); // dada una cara y un nodo de esa cara, retorna el indice de la cara vecina a la cara dada que esta opuesta al nodo dado. (Si la cara tiene 3 lados es una sola cara, asi que por el momento retorno solo un indice, despues se puede generalizar).
        vector<int> getArcosNoIncidentes(int ind_cara, int ind_nodo); // retorna los indices de los arcos de la cara ind_cara que no son incidentes en el vertice ind_nodo
        vector<int> getCarasVecinasSinNodo(int ind_cara, int ind_nodo); // retorna los indices de las caras vecinas a la cara ind_cara y que no tienen como vértice a ind_nodo
        int getArcoDiferente(int ind_cara, int ind_arco, int ind_nodo); // retorna el índice del arco que pertenece a la cara ind_cara y que es incidente en el nodo, pero que no es el arco ind_arco

        // otros métodos:
        void setNormales(); // setea las normales de cada punto perteneciente a la malla como el promedio de las normales de las caras adyacentes al punto.
        Vect getNormalNodos(int ind_p1, int ind_p2, int ind_p3); // retorna la normal al plano formado por los 3 puntos pasados como parametro.
        int checkMalla(bool imprimir);	//Chequea que la malla sea consistente. Que no hayan punteros al vacio.
		int checkCara(int indCara, bool imprimir); //Chequea que los arcos y caras a los que apunta el nodo apunten también a él
		int checkCara_debil(int indCara, bool imprimir); //Chequea que los arcos y caras a los que apunta el nodo apunten también a él. No chequea que los arcos y nodos de las caras sean consistentes
		int checkArco(int indArco, bool imprimir); //Chequea que los nodos y caras a los que apunta el arco apunten también a él
		int checkNodo(int indNodo, bool imprimir); //Chequea que los arcos y nodos a los que apunta la cara apunten también a ella
		string getTipoMalla();

        // métodos dirigidos al desplazamiento de la malla:
        vector<double> getValoresVolumenCero(int ind_arco);
        int getTipoMovRegion(int ind_arco, double val); // movemos los puntos pertenecientes a la region y vemos que tipo de region es. Luego volvemos los puntos a donde estaban y retornamos el tipo de la region.
        int tipArco(int ind_arco);
        int puntoInCara(Punto p, int ind_cara); // ve si el punto p esta dentro de la cara o no. Una pre-condicion es que el punto pertenesca al plano que forma la cara.
        int seCruzan(Punto p1_arco1, Punto p2_arco1, Punto p1_arco2, Punto p2_arco2); // ve si los arcos se cruzan o no.
        double valorInterseccion(Punto p1_arco1, Punto p2_arco1, Punto p1_arco2, Punto p2_arco2); // retorna el valor de interseccion segun el arco1, es decir, el punto de interseccion estara multiplicando el vector arco1 por el valor retornado. Los puntos deben estar en el mismo plano.

        //Metodos para la medula
        void recalcularMedula();

		//Debugging
		void print();
		void printfile();

		//Destructor
		virtual ~Malla();

};

#endif
