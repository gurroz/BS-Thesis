#ifndef CARA_H
#define CARA_H

#include <cassert>
#include <vector>
#include <set>
#include <iostream>
#include <string>
#include <sstream>
#include "malla.h"

using namespace std;

class Malla;
class Arcos;

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
Esta clase representa una cara del objeto a modelar. Posee una lista de indices a los puntos que
forman la cara, y una lista de indices a los arcos que forman la cara.
 */
class Cara {
    protected:
        vector<int> ind_nodos; // Lista de indices a los nodos de la cara (no necesariamente en orden de la mano derecha)
        vector<int> ind_arcos; // Lista de indices a los arcos de la cara (no necesariamente en orden de la mano derecha)
        int num_elem; // Numero de puntos y arcos de la cara
        float rgb[3]; // color de la cara al visualizarla
        //bool invariante();
    public:
    	// Contructores
        Cara();
        Cara(int n1, int n2, int n3, int a1, int a2, int a3); // crea una cara con 3 elementos --> un triángulo
        Cara(int n1, int n2, int n3);
        Cara(vector<int> ind_pts, vector<int> ind_arcs); // crea una cara con la lista de índices dados

        virtual Cara *clone();

        virtual ~Cara() {};

		// Getters
        vector<int> getArcos(); // get de la lista de arcos
		vector<int> getNodos(); // get de la lista de nodos
		int getNumElem(); // get del numero de elementos de la cara (numero de vertices o arcos)
        float getR();
        float getG();
        float getB();

		// Setters
        void setArcos(vector<int> ars); // set de la lista de arcos
        void setNodos(vector<int> nds); // set de la lista de nodos
        void setColores(float r, float g, float b); // set de los colores.

		// Otros métodos
        void addNodo(int nodo); // se inserta el nodo solo si no esta insertado antes
        void eraseNodo(int nodo); // borra el nodo si esta.
        void changeNodo(int nodo_sale, int nodo_entra); // cambia el indice nodo_sale por el indice nodo_entra. Si no encuentro nodo_sale no hago nada.
        vector<int> changeNodoCascada(int nodo_sale, int nodo_entra, Arcos *arcos); // cambia el indice nodo_sale por el indice nodo_entra, tanto en la cara como en sus arcos. Si no encuentro nodo_sale no hago nada.

        void addArco(int arco); // se inserta el arco solo si no esta insertado antes
        void eraseArco(int arco); // borra la cara si esta.
        void changeArco(int arco_sale, int arco_entra);

        int getPuntoDistinto(int p1, int p2); // solo para una cara triangular, retorna el indice que es distinto a los indices pasados como parametros.
        vector<int> getPuntosDistintos(int p1); // devuelve los índices (dos o tres) de los nodos de la cara que son distintos al índice del punto
        vector<int> getArcosNoIncidentes(int ind_nodo, Malla *malla); // devuelve los indices de los arcos de la cara no incidentes en el nodo
        vector<int> getArcosIncidentes(int ind_nodo, Malla *malla);

        bool perteneceArco(int ind_arco); // indica si el arco pertenece a la cara
        bool perteneceNodo(int ind_nodo); // indica si el nodo pertenece a la cara
        virtual string getEtiqueta(); // indica si la cara es de tipo "triangular" o "quadrilateral"

        double getArea(Malla *malla); // retorna el área de la cara en el índice.
		double getPerimetro (Malla *malla);	//retorna el perimetro de la cara en el indice.
        double getAnguloVertice(int ind_nodo,Malla *malla); // retorna el ángulo en la cara ind_cara y el nodo ind_nodo.
        double getAnguloMin(Malla *malla); // retorna el ángulo mínimo de la cara en el índice
        double getAnguloMax(Malla *malla); // retorna el ángulo máximo de la cara en el índice
        vector<int> getArcosAnguloMin(Malla *malla); // retorna los índices de los 2 arcos que forman el ángulo mínimo de la cara
        int getNodoAnguloMin(Malla *malla); // retorna el índice del nodo que es vértice del ángulo min.
        int getNodoAnguloMax(Malla *malla); // retorna el índice del nodo que es vértice del ángulo máx.
        Vect getNormal(Malla *malla); // retorna el vector normal de esa cara
        int getArcoMasLargo(Malla *malla); // retorna el indice del arco mas largo en la cara ind_cara.
        int getArcoMasCorto(Malla *malla); // retorna el indice del arco mas corto en la cara ind_cara.

        // Transformaciones
        virtual Cara *colapsarArco(Malla *malla,int ind_arco, int ind_nodo); // colapsa un arco borrando un nodo y entrega la cara resultante (null si la cara desaparece)

		void ordenar(Malla *malla); // ordena los arcos para que coincidan con el orden de los nodos

        bool check(Malla *malla); // chequea condiciones básicas de consistencia de la cara: arcos y nodos distintos y nodos no colineales

        friend ostream& operator<<(ostream &os, Cara *c);
        string imprimir();
};

#endif
