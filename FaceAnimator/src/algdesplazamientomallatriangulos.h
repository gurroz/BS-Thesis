#ifndef ALGDESPLAZAMIENTOMALLATRIANGULOS_H
#define ALGDESPLAZAMIENTOMALLATRIANGULOS_H

#include "malla.h"
#include "algdesplazamiento.h"

/**
@author Cristina Melo
 */
class AlgDesplazamientoMallaTriangulos : public AlgDesplazamiento {
    public:
        virtual void aplicar(Malla *malla) = 0;
		virtual ~AlgDesplazamientoMallaTriangulos(){}
};

#endif
