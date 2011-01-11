#ifndef MEJDELAUNAY_H
#define MEJDELAUNAY_H

#include "algmejoramientomallatriangulos.h"
/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
 * Algoritmo que mejora la malla maximizando el ángulo mínimo de las caras mediante flips de arcos
 */
class MejDelaunay : public AlgMejoramientoMallaTriangulos {
    public:
        MejDelaunay();
        void aplicar(Malla *malla);
};

#endif
