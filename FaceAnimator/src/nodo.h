#ifndef NODO_H
#define NODO_H

#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <sstream>

#include "punto.h"
#include "vect.h"

using namespace std;

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
Esta clase se utiliza para la representación de un punto dentro de una malla
 */
class Nodo {
    private:
        Punto p; // Punto en el espacio 3D que representa.
        Vect normal; // Vector de desplazamiento del Punto. Es un rayo saliente.
        double concentracion; // Modulo del desplazamiento del nodo.
        vector<int> caras; // Lista de indices a las caras que tienen este nodo.
        vector<int> arcos; // Lista de indices a los arcos que tienen este nodo.
        double textureX, textureY;
        int close1, close2, close3;
        double coef1, coef2, coef3;
        Nodo *original;
    public:
        Nodo();
        Nodo(Punto p);
        Nodo *clone();

        // getters y setters.
        void setPunto(Punto p);
        Punto getPunto();

        void setNormal(Vect n);
        Vect getNormal();
        void setConcentracion(double con);
        double getConcentracion();
        void setCaras(vector<int> crs);
        vector<int> getCaras();
        void setArcos(vector<int> ars);
        vector<int> getArcos();

        void addCara(int cara); // se agrega la cara a la lista de caras solo si no estaba insertada antes.
        void addCaraConRepeticion(int cara); // se agrega la cara a la lista de caras, aunque ya estuviera antes (posteriormente se borrará la cara repetida)
        void eraseCara(int cara); // borra la cara de la lista de caras solo si esta.
        void addArco(int arco); // se agrega el arco a la lista de arcos solo si no estaba insertado antes.
        void eraseArco(int arco); // borra el arco de la lista de arcos solo si esta.
		bool changeCara(int cara_sale, int cara_entra); // si el nodo pertenece a la cara, se cambia el índice de la cara
		bool changeArco(int arco_sale, int arco_entra); // si el nodo pertenece al arco, se cambia el índice del arco

        bool perteneceACara(int ind_cara); // Indica si a la cara pertenece el nodo
        bool perteneceAArco(int ind_arco); // Indica si al arco pertenece el nodo

        string imprimir(); // imprime a la salida estandar las coordenadas del Punto p.
        friend ostream& operator<<(ostream &os, Nodo *n);

        void setTexturePoint(double p1, double p2);
        double getTextureX();
        double getTextureY();

        void asociarNodos(int i1, double c1, int i2, double c2, int i3, double c3);
        int getAsociado1();
        int getAsociado2();
        int getAsociado3();
        double getCoef1();
        double getCoef2();
        double getCoef3();
        float distancia(Nodo* n);
        void setNewPunto(Punto p);
        Nodo *getOriginalNodo();
		~Nodo();
};

#endif
