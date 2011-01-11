#ifndef ALGDESREFINAMIENTOMALLATRIANGULOS_H
#define ALGDESREFINAMIENTOMALLATRIANGULOS_H

#include "algdesrefinamiento.h"

/**
@author Cristina Melo
 */
class AlgDesrefinamientoMallaTriangulos : public AlgDesrefinamiento {
    public:
        virtual void aplicar(Malla *malla, Criterio *criterio) = 0;
		virtual ~AlgDesrefinamientoMallaTriangulos(){}
};

#endif

