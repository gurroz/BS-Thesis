#ifndef ALGDESPLAZAMIENTOMALLACUADRILATEROS_H
#define ALGDESPLAZAMIENTOMALLACUADRILATEROS_H

#include "malla.h"
#include "algdesplazamiento.h"

/**
@author Cristina Melo
 */
class AlgDesplazamientoMallaCuadrilateros : public AlgDesplazamiento {
    public:
        virtual void aplicar(Malla *malla) = 0;
		virtual ~AlgDesplazamientoMallaCuadrilateros(){}
};

#endif

