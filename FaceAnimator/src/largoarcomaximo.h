#ifndef LARGOARCOMAXIMO_H
#define LARGOARCOMAXIMO_H

#include "criterio.h"

/**
@author Nicolas Silva Herrera
Clase que verifica si el arco mas largo de una cara supera el maximo entregado.
 */
class LargoArcoMaximo:public Criterio {
    private:
        double max;
    public:
        LargoArcoMaximo(double max);
        bool seCumple(Malla *malla, int indCara);

};

#endif
