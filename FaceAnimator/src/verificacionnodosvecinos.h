#ifndef VERIFICACIONNODOSVECINOS_H
#define VERIFICACIONNODOSVECINOS_H

#include "algdesplazamientomallatriangulos.h"

/**
@author Nicolas Silva Herrera
 * Desplaza los elementos de la malla basandose en verificaciones por nodos vecinos.
 */
class VerificacionNodosVecinos : public AlgDesplazamientoMallaTriangulos {
    public:
        VerificacionNodosVecinos(double val);
        void aplicar(Malla *malla);
	private:
        double val;
		int nnodosborrados;
		int repairMalla(Malla *malla);	//Repara la malla de acuerdo a las inconsistencias que se van a producir. Retorna el numero de inconsistencias que encontro.
        double moverHasta(Malla *malla); // mueve la malla una proporcion val de la concentracion de cada nodo, maximo 1.0
		bool checkInterseccionNodo(Malla* malla, int indNodo);	//Chequea si la proyeccion de ese nodo intersecta con el cilindro de proyeccion que lo envuelve.
		bool corrigeInconsistencia (Malla *malla, int indNodo);	//Corrige la inconsistencia. Si no puede, retorna false.
		void borrarNodoCentral(Malla* malla, int indNodo);
};

#endif
