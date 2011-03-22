#ifndef MOVIMIENTOSAUV_H_INCLUDED
#define MOVIMIENTOSAUV_H_INCLUDED

#include "movimientosNodos.h"

class MovimientosAUV : public MovimientosNodos {
    public:
        MovimientosAUV();
        Punto *getMovimiento(int number_nodo, int indice_unit);

};


#endif // MOVIMIENTOSAUV_H_INCLUDED
