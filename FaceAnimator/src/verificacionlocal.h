#ifndef VERIFICACIONLOCAL_H
#define VERIFICACIONLOCAL_H

#include <map>
#include <list>

#include "algdesplazamientomallatriangulos.h"

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
 * Desplaza los elementos de la malla basandose en verificaciones locales
 */
class VerificacionLocal : public AlgDesplazamientoMallaTriangulos {
    private:
        double val;
        double moverHastaPrimeraInconsistencia(Malla *malla); // mueve la malla hasta la primera inconsistencia o cada nodo hasta su concentración. Retorna el valor movido.
        double moverHasta(Malla *malla); // mueve la malla una proporcion val de la concentracion de cada nodo, maximo 1.0
    public:
        VerificacionLocal(double val); //val indica la proporcion a desplazar. Si es -1 desplaza hasta la primera inconsistencia.
        void aplicar(Malla *malla);
};

#endif
