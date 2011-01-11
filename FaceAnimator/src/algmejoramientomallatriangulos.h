#ifndef ALGMEJORAMIENTOMALLATRIANGULOS_H
#define ALGMEJORAMIENTOMALLATRIANGULOS_H

#include "algmejoramiento.h"

/**
@author Cristina Melo
 */
class AlgMejoramientoMallaTriangulos : public AlgMejoramiento {
    public:
        virtual void aplicar(Malla *malla) = 0;
		virtual ~AlgMejoramientoMallaTriangulos(){}
};

#endif
