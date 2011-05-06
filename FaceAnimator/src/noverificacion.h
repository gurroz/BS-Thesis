#ifndef NOVERIFICACION_H
#define NOVERIFICACION_H

#include "algdesplazamientomallatriangulos.h"
#include "algdesplazamientomallacuadrilateros.h"

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
 * Desplaza los elementos de la malla sin considerar su consistencia, solo hay cambios geométricos.
 */
class NoVerificacion : public AlgDesplazamientoMallaTriangulos, public AlgDesplazamientoMallaCuadrilateros {
    private:
        double val;
    public:
        NoVerificacion(double val);
        void aplicar(Malla *malla);
        void moverNodosSegunParametro(int ind, double val, Malla *malla){};
};

#endif
