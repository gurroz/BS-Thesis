#ifndef ALGREFINAMIENTOMALLACUADRILATEROS_H
#define ALGREFINAMIENTOMALLACUADRILATEROS_H

#include "algrefinamiento.h"

/**
@author Cristina Melo
 */
class AlgRefinamientoMallaCuadrilateros : public AlgRefinamiento {
    public:
        virtual void aplicar(Malla *malla, Criterio *criterio) = 0;
		virtual ~AlgRefinamientoMallaCuadrilateros(){}
};

#endif

