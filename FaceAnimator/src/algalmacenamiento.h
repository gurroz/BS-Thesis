#ifndef ALGALMACENAMIENTO_H
#define ALGALMACENAMIENTO_H

#include "malla.h"

/**
@author Nicolas Silva Herrera
Interfaz para los algoritmos de almacenamiento de la malla.
 */
class AlgAlmacenamiento {
    public:
        virtual void aplicar(Malla *malla, string filename) = 0;
		virtual ~AlgAlmacenamiento(){};
};

#endif
