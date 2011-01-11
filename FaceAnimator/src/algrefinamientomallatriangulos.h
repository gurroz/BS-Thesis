#ifndef ALGREFINAMIENTOMALLATRIANGULOS_H
#define ALGREFINAMIENTOMALLATRIANGULOS_H

#include "algrefinamiento.h"

/**
@author Cristina Melo
 */
class AlgRefinamientoMallaTriangulos : public AlgRefinamiento {
    public:
        virtual void aplicar(Malla *malla, Criterio *criterio) = 0;
		virtual ~AlgRefinamientoMallaTriangulos(){}
};

#endif
