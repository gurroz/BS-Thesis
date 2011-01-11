#ifndef MOVIMIENTOSNODOS_H_INCLUDED
#define MOVIMIENTOSNODOS_H_INCLUDED

#include "punto.h"

class MovimientosNodos{
  public:
        virtual Punto *getMovimiento(int number_nodo, int indice_unit) = 0;
};


#endif // MOVIMIENTOSNODOS_H_INCLUDED
