#ifndef PUNTO_H
#define PUNTO_H

#include <iostream>
#include <cassert>




using namespace std;

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
Esta clase se utilizará para la representación de un punto específico en el espacio 3D
 */
class Punto {
    private:
        double x; //primera coordenada del punto
        double y; //segunda coordenada del punto
        double z; //tercera coordenada del punto
    public:
        Punto(); // constructor del punto en el origen (0,0,0)
        Punto(double x, double y, double z); // constructor con cada una de las coordenadas
        void setX(double x); // set de la primera coordenada
        void setY(double y); // set de la segunda coordenada
        void setZ(double z); // set de la tercera coordenada
        double getX(); // get de la primera coordenada
        double getY(); // get de la segunda coordenada
        double getZ(); // get de la tercera coordenada
        double operator[](int indice); // get de las coordenadas mediante subindices [0]=x; [1]=y; [2]=z
        bool operator==(Punto p); // igualdad de Puntos
        bool operator!=(Punto p); // desigualdad de Puntos
        friend ostream& operator<<(ostream &os, Punto p); // imprime a la salida estandar las coordenadas del punto
};

#endif


