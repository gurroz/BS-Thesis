#ifndef VECT_H
#define VECT_H

#include <iostream>
#include <cassert>
#include <math.h>

#include "definiciones.h"
#include "punto.h"

using namespace std;

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
Esta clase representa a un vector. Sirve para realizar las operaciones básicas sobre vectores,
como son su largo, producto punto, producto cruz, suma, resta y multiplación (por escalar). Además ángulo entre 2 vectores.
 */
class Vect {
    private:
        Punto p; // El vector es representado como la resta entre el punto p y el punto Origen=(0,0,0).
    public:
        Vect(); // Vector de largo 0, es decir, con p en el origen.
        Vect(Punto p); // Vector con punto p
        Vect(double x, double y, double z); // vector con Punto p = new Punto(x,y,z).
        void setPunto(Punto p); // set del punto que representa al vector.
        Punto getPunto(); // get del punto que representa al vector.
        bool inOrigen(); // verdadero si el Punto p es el origen, falso de lo contrario.
        double largo(); // retorna el largo del vector (desde la coordenada (0,0,0) hasta la coordenada del punto actual).
        double getAngulo(Vect v); // retorna el angulo entre los 2 vectores.
        double prodPunto(Vect v); // retorna el producto punto entre los 2 vectores.
        Vect prodCruz(Vect v); // retorna el producto cruz entre los 2 vectores.
        Vect operator*(double x); // multiplicación del vector por un escalar.
        Vect operator+(Vect v); // suma entre ambos vectores.
        Vect operator-(Vect v); // resta entre ambos vectores.
        bool operator==(Vect v); // igualdad entre ambos vectores.
        bool operator!=(Vect v); // desigualdad entre ambos vectores.
        void normalizar();  //Normaliza el vector.
        friend ostream& operator<<(ostream &os, Vect v); // imprime el punto del vector.
		~Vect();

		Vect proyectadoEn(Vect v1, Vect v2, Vect v3);  //devuelve la proyección del vector sobre el plano formado por v1,v2,v3
		bool estaEnTriangulo(Vect v1, Vect v2, Vect v3);  //entrega si el vector está dentro del triángulo formado por v1,v2,v3
};

#endif
