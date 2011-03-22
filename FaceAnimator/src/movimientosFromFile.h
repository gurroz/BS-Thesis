#ifndef MOVIMIENTOSFROMFILE_H_INCLUDED
#define MOVIMIENTOSFROMFILE_H_INCLUDED

#include "movimientosNodos.h"

class MovimientosFromFile : public MovimientosNodos {
    public:
        MovimientosFromFile(string filename);
        Punto *getMovimiento(int number_nodo, int indice_unit);
        ~MovimientosFromFile();
    private:
        int N;
        int *sizes;
        int **nodes;
        float ***values;

};

#endif // MOVIMIENTOSFROMFILE_H_INCLUDED
