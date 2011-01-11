#ifndef ARCOS_H
#define ARCOS_H

#include "nodo.h"
#include "nodos.h"
#include "arco.h"
#include "vect.h"

class Arco;

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
Esta clase es un contenedor de arcos, es decir, representa un conjunto de arcos
 */
class Arcos {
    private:
        vector<Arco*> arcos; // lista de arcos
        vector<int> borrados; // lista de indices a arcos que han sido borrados.
        int num_arcos; // numero de arcos totales almacenados, incluyendo los borrados, debe ser igual a arcos.size()
        int num_arcos_validos; // numero de arcos almacenados que no han sido borrados, debe ser igual a arcos.size() - borrados.size()
	protected:
        Arcos(Arcos *a); // constructor de copia
    public:
        Arcos(); // crea un contenedor de arcos con 0 arcos
        Arcos(Arco *a); // crea un contenedor de arcos con 1 arco
        Arcos(vector<Arco*> arcs); // crea un contenedor con un conjunto de arcos
        Arcos *clone();
        int addArco(Arco *a); // agrega un arco al contenedor.
        int addArcoIn(Arco *a, int indice); // agrega el arco "a" al contenedor en la posicion "indice". Si habia otro arco en indice se borra.
        void eraseArco(int indice); // borra el arco en ese indice si no estaba borrado.
        void setCaraArco(int indice, int ind_cara); // setea en ese arco el indice a la cara que comparte
        Arco* getArco(int indice); // get del arco en ese posicion
        Arco* operator[](int indice); // get del arco en ese posicion
        int getNumArcos(); // número de arcos totales
        int getNumArcosValidos(); // número de arcos válidos
        int getIndiceArco(int indice_n1, int indice_n2); // retorna el indice donde esta el arco que tiene esos indices a nodos. Si no esta inserta ese arco lo inserta y retorna el indice donde lo inserto.
        int getNodoComun(int indice_a1, int indice_a2); // retorna el índice del nodo común a los dos arcos
        friend ostream& operator<<(ostream &os, Arcos *a);
		~Arcos();
};

#endif
