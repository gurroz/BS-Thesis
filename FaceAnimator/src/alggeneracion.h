#ifndef ALGGENERACION_H
#define ALGGENERACION_H

#include "malla.h"
#include "mallatriangulos.h"
#include "mallacuadrilateros.h"
#include "LoadTextures.h"

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
Interfaz para los algoritmos de generación de la malla del objeto a modelar
 */
class AlgGeneracion {
    public:
        virtual Malla* aplicar() = 0;
		virtual ~AlgGeneracion(){}
};

#endif
