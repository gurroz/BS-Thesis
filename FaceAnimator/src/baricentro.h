#ifndef BARICENTRO_H
#define BARICENTRO_H

#include "algcentrotriangulo.h"

/**
@author Cristina Melo
 */
class Baricentro : public AlgCentroTriangulo {
    public:
        Baricentro(Malla *malla);
        Punto getCentro(Triangulo *triangulo);
        double getConcentracionCentro(Triangulo *triangulo);
};

#endif


