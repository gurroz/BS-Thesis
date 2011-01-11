#ifndef ALGDESREFINAMIENTO_H
#define ALGDESREFINAMIENTO_H

#include "malla.h"
#include "criterio.h"

/**
@author Nicolas Silva Herrera
Interfaz para los algoritmos de desrefinamiento de las mallas.
 */

class Criterio;

class AlgDesrefinamiento {
    public:
        virtual void aplicar(Malla *malla, Criterio *criterio) = 0;
		virtual ~AlgDesrefinamiento(){}
};

#endif
