#ifndef ALGMEJORAMIENTOMALLATRIANGULOS_H
#define ALGMEJORAMIENTOMALLATRIANGULOS_H

#include "algmejoramiento.h"

/**
@author Cristina Melo
 */
class AlgMejoramientoMallaTriangulos : public AlgMejoramiento {
    public:
        virtual void aplicar(Malla *malla)=0;
        virtual Punto *getMovimiento(int number_nodo, int indice_unit)=0;
		virtual ~AlgMejoramientoMallaTriangulos(){}

};

#endif
