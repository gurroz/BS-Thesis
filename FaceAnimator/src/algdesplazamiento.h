#ifndef ALGDESPLAZAMIENTO_H
#define ALGDESPLAZAMIENTO_H

#include "malla.h"

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
Interfaz para los algoritmos de desplazamiento de los nodos de la malla
 */
class AlgDesplazamiento {
    public:
        virtual void aplicar(Malla *malla) = 0;
		virtual ~AlgDesplazamiento(){}
};

#endif
