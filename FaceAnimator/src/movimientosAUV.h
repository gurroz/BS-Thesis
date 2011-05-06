#ifndef MOVIMIENTOSAUV_H_INCLUDED
#define MOVIMIENTOSAUV_H_INCLUDED

#include "algdesplazamientomallatriangulos.h"

class MovimientosAUV : public AlgDesplazamientoMallaTriangulos {
    public:
        MovimientosAUV();
        void aplicar(Malla *malla);
        Punto *getMovimiento(int number_nodo, int indice_unit);
        void moverNodosSegunParametro(int ind, double val, Malla *malla);
};


#endif // MOVIMIENTOSAUV_H_INCLUDED
