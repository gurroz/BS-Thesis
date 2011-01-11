#ifndef NODOS_H
#define NODOS_H

#include <vector>
#include <gsl/gsl_poly.h>

#include "nodo.h"
#include "vect.h"

using namespace std;

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
Esta clase es un contenedor de nodos, es decir, representa un conjunto de nodos
 */

class Nodos {
    private:
        vector<Nodo*> nodos; // lista de nodos.
        int num_nodos; // número total de nodos almacenados, debe ser igual a nodos.size().
        int num_nodos_validos; // número de nodos almacenados que no han sido borrados, debe ser igual a nodos.size() - borrados.size().
        vector<int> borrados; // lista de índices a nodos que han sido borrados.
        double maxx, maxy, minx, miny, maxz, minz;

	protected:
        Nodos(Nodos *n); // constructor de copia
    public:
            int *nodos_marcados;
            int n_marcados;
        Nodos(); // crea un contenedor vacío.
        Nodos(vector<Nodo*> nds); // crea un contenedor a partir de una lista de nodos.
        Nodos *clone();
        int addNodo(Nodo* n); // agrega un nodo al contenedor y retorna el índice donde lo dejo.
        void eraseNodo(int indice); // borra el nodo de esa posición si no estaba borrado antes.
        Nodo* getNodo(int indice); // retorna el nodo en esa posición.
        Nodo* operator[](int indice); // retorna el nodo en esa posición.

        // Métodos de movimiento del nodo:
        void moverNodo(int indice, double dist); // mueve el nodo en el indice utilizando la informacion de su movimiento.
        void moverNodoSegunConcentracion(int indice, double val);
        void regresarNodo(int indice, double dist); // mueve el nodo en la direccion contraria de la normal de movimiento.
        void regresarNodoSegunConcentracion(int indice, double val);
        void moverTodos(double dist);
        void moverTodosSegunConcentracion(double val);

        void moverNodoWithTexture(int indice, double x, double y, double z, double dist);
        void moverNodo(int indice, double x, double y, double z, double dist); // mueve el nodo en el indice, en la direccion y la distancia indicadas.
        void moverTodosAUV(int indice, double dist); //mueve los nodos de acuerdo a las AnimationUnit
        void moverShapeUnit(int indice, double dist); //mueve los nodos de acuerdo a las AnimationUnit

        Punto *movimientoAUV(int number_nodo, int indice_unit);
        void asignar_nodos_marcados(int *clos, int num);

        double get_maxx();
        double get_minx();
        double get_maxy();
        double get_miny();
        double get_maxz();
        double get_minz();

        int getNumNodos(); // retorna el número total de nodos
        int getNumNodosValidos(); // retorna el número de nodos válidos
        void addCaraNodo(int indice, int cara); // agrega el indice de la cara al nodo en esa posicion
        void addArcoNodo(int indice, int arco); // agrega el indice del arco al nodo en esa posicion
        int popNodoVacio(int indice); // saca un nodo vacio del conjunto, intercambiandolo con el ultimo que no sea vacio, retornamos este ultimo indice.
        friend ostream& operator<<(ostream &os, Nodos *n);

		//Destructor
		~Nodos();
};

#endif
