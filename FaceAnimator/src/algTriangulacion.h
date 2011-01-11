#ifndef ALGTRIANGULACION_H
#define ALGTRIANGULACION_H

#include "malla.h"

/**
@author Cristina Melo
 */
class AlgTriangulacion {
    public:
    	virtual void aplicar(Malla *malla) = 0;
    	virtual ~AlgTriangulacion() {};
};

#endif


