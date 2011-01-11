#ifndef ALGMEJORAMIENTOMALLACUADRILATEROS_H
#define ALGMEJORAMIENTOMALLACUADRILATEROS_H

#include "algmejoramiento.h"

/**
@author Cristina Melo
 */
class AlgMejoramientoMallaCuadrilateros : public AlgMejoramiento {
    public:
        virtual void aplicar(Malla *malla) = 0;
		virtual ~AlgMejoramientoMallaCuadrilateros(){}
};

#endif

