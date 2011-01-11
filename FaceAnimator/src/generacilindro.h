#ifndef GENERACILINDRO_H
#define GENERACILINDRO_H

#include "alggeneracion.h"
#include "triangulo.h"
#include "cuadrilatero.h"
#include <math.h>

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
 */
class GeneraCilindro : public AlgGeneracion
{
    private:
        Nodos* nodos;
        Arcos* arcos;
        Caras* caras;
        double altura; // altura del cilindro
        double radio; // radio del cilindro
        int num_anillos; // número de anillos del cilindro
        int num_puntos; // número de puntos por cada anillo del cilindro
        int tipo; // tipo de malla. tipo=0 => triangulos. tipo=1 => cuadrilateros.
        Malla* generaMallaTriangulos(); // genera una malla de triangulos del cilindro
        Malla* generaMallaCuadrilateros(); // genera una malla de cuadriláteros del cilindro
        void updateVecinos();   //Actualiza los vecinos de los elementos de la malla

    public:
        GeneraCilindro(double altura=5, double radio=1, int num_anillos=20, int num_puntos=10, int tipo=0);
        Malla* aplicar();
};

#endif
