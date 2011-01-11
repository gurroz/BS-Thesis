#ifndef LARGOARCOMINIMO_H
#define LARGOARCOMINIMO_H

#include "criterio.h"

/**
@author Nicolas Silva Herrera
Clase que verifica si el arco mas corto de una cara supera el maximo entregado.
 */
class LargoArcoMinimo:public Criterio {
    private:
        double max;
    public:
        LargoArcoMinimo(double max);
        bool seCumple(Malla *malla, int indCara);

};

#endif
