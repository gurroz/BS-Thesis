#ifndef ALGMEJORAMIENTO_H
#define ALGMEJORAMIENTO_H

#include "malla.h"

/**
@author Nicolas Silva
Interfaz para los algoritmos de mejoramiento de las mallas
 */
class AlgMejoramiento {
    public:
        virtual void aplicar(Malla *malla) = 0;
		virtual ~AlgMejoramiento(){}
};

#endif
