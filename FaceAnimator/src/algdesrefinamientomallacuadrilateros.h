#ifndef ALGDESREFINAMIENTOMALLACUADRILATEROS_H
#define ALGDESREFINAMIENTOMALLACUADRILATEROS_H

#include "algdesrefinamiento.h"

/**
@author Cristina Melo
 */
class AlgDesrefinamientoMallaCuadrilateros : public AlgDesrefinamiento {
    public:
        virtual void aplicar(Malla *malla, Criterio *criterio) = 0;
		virtual ~AlgDesrefinamientoMallaCuadrilateros(){}
};

#endif


