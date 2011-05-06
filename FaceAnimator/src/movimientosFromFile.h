#ifndef MOVIMIENTOSFROMFILE_H_INCLUDED
#define MOVIMIENTOSFROMFILE_H_INCLUDED

#include "algdesplazamientomallatriangulos.h"

class MovimientosFromFile : public AlgDesplazamientoMallaTriangulos {
    public:
        MovimientosFromFile(string filename);
        void aplicar(Malla *malla);
        Punto *getMovimiento(int number_nodo, int indice_unit);
        void moverNodosSegunParametro(int ind, double val, Malla *malla);
        ~MovimientosFromFile();
    private:
        int N;
        int *sizes;
        int **nodes;
        float ***values;

};

#endif // MOVIMIENTOSFROMFILE_H_INCLUDED
