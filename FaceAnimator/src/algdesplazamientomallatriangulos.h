#ifndef ALGDESPLAZAMIENTOMALLATRIANGULOS_H
#define ALGDESPLAZAMIENTOMALLATRIANGULOS_H

#include "algdesplazamiento.h"

/**
@author Cristina Melo
 */
class AlgDesplazamientoMallaTriangulos : public AlgDesplazamiento {
    public:
        virtual void aplicar(Malla *malla) = 0;
        virtual void moverNodosSegunParametro(int ind, double val, Malla *malla) = 0;
		virtual ~AlgDesplazamientoMallaTriangulos(){}
};

#endif
