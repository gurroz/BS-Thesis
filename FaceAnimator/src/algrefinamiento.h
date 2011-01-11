#ifndef ALGREFINAMIENTO_H
#define ALGREFINAMIENTO_H

#include "malla.h"
#include "criterio.h"

/**
@author Nicolas Silva Herrera
Interfaz para los algoritmos de refinación de las mallas
 */
class AlgRefinamiento {
    public:
        virtual void aplicar(Malla *malla, Criterio *criterio) = 0;
		virtual ~AlgRefinamiento(){}
};

#endif
