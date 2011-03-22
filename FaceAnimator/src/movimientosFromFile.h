#ifndef MOVIMIENTOSFROMFILE_H_INCLUDED
#define MOVIMIENTOSFROMFILE_H_INCLUDED

#include "algmejoramientomallatriangulos.h"

class MovimientosFromFile : public AlgMejoramientoMallaTriangulos {
    public:
        MovimientosFromFile(string filename);
        Punto *getMovimiento(int number_nodo, int indice_unit);
        void aplicar(Malla *malla);
        ~MovimientosFromFile();
    private:
        int N;
        int *sizes;
        int **nodes;
        float ***values;

};

#endif // MOVIMIENTOSFROMFILE_H_INCLUDED
