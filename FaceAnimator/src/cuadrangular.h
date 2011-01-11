#ifndef CUADRANGULAR_H
#define CUADRANGULAR_H

#include "comando.h"
#include "algcentrotriangulo.h"
#include "mallacuadrilateros.h"

/**
@author Cristina Melo
*/
class Cuadrangular : public Comando {
    private:
        AlgCentroTriangulo *algoritmo;
        MallaCuadrilateros *nueva_malla;
    public:
        Cuadrangular(Malla *m, AlgCentroTriangulo *a);
        void execute();
        MallaCuadrilateros *getMalla();
		~Cuadrangular();
};

#endif
