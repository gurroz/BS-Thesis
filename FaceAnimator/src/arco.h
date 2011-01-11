#ifndef ARCO_H
#define ARCO_H

#include "malla.h"
#include "punto.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <sstream>

using namespace std;

class Malla;

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
Esta clase representa un arco, el cual está formado por 2 índices a un conjunto de puntos
 */
class Arco {
    private:
        int nodo1; // indice al primer nodo que define el arco
        int nodo2; // indice al segundo nodo que define el arco
        int cara1; // indice a una de las caras que tiene este arco
        int cara2; // indice a la otra cara que tiene este arco
    public:
        Arco();
        Arco(int n1, int n2);
        Arco(int n1, int n2, int c1, int c2);
        Arco *clone();

        // setters y getters:
        void setNodo1(int n1);
        void setNodo2(int n2);
        void setNodos(int n1, int n2);
        void setCara1(int c1);
        void setCara2(int c2);
        void setCara(int c); //inserta la cara en el espacio desocupado, cara1 o cara2
        void setCaras(int c1, int c2);
        bool changeNodo(int nodo_sale, int nodo_entra); //si nodo_entra pertenece al arco, lo cambia por nodo_sale. Indica si el cambio se produjo
        bool changeCara(int cara_sale, int cara_entra); //si el arco pertenene a cara_entra, cambia la cara por cara_sale
        int getNodo1();
        int getNodo2();
        int getCara1();
        int getCara2();
        int getCaraDistinta(int c); //Entrega la cara diferente a la que se pasó como argumento
		int getNodoDistinto(int n);	//Entrega el nodo diferente al que se le paso como argumento
		bool estanNodos(vector<int> nodos); //Retorna true si dentro de la lista estan los nodos que componen el arco.
		bool perteneceNodo(int ind_nodo); // Indica si el nodo forma parte del arco
		bool perteneceACara(int ind_cara); // Indica si a la cara pertenece el arco

        // métodos arcos:
        double getLargo(Malla *malla);
        Punto getPuntoMedio(Malla *malla);

        // imprime los indices
        friend ostream& operator<<(ostream &os, Arco *a);
        string imprimir();
};

#endif
