#ifndef CRITERIO_H
#define CRITERIO_H

#include "malla.h"

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
 */
class Criterio{
    public:
        virtual bool seCumple(Malla *malla, int indice) = 0;
		virtual ~Criterio(){}
};

#endif
