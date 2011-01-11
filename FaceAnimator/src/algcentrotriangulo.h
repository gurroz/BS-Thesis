#ifndef ALGCENTROTRIANGULO_H
#define ALGCENTROTRIANGULO_H

#include "triangulo.h"
#include "malla.h"
#include "punto.h"

/**
@author Cristina Melo
 */
class AlgCentroTriangulo {
	protected:
		Malla *_malla;
    public:
    	AlgCentroTriangulo(Malla *malla) {
    		_malla = malla;
		}
        virtual Punto getCentro(Triangulo *triangulo) = 0;
        virtual double getConcentracionCentro(Triangulo *triangulo) = 0;
		virtual ~AlgCentroTriangulo(){}
};

#endif

