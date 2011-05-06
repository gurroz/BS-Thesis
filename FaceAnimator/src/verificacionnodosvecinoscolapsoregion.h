#ifndef VERIFICACIONNODOSVECINOSCOLAPSOREGION_H
#define VERIFICACIONNODOSVECINOSCOLAPSOREGION_H

#include "algdesplazamientomallatriangulos.h"
#include "algdesplazamientomallacuadrilateros.h"
/**
 * Desplaza los elementos de la malla basandose en verificaciones por nodos vecinos.
 * Si no se puede reparar la trayectoria, se colapsa la región
 */
class VerificacionNodosVecinosColapsoRegion : public AlgDesplazamientoMallaTriangulos, public AlgDesplazamientoMallaCuadrilateros {
    public:
        VerificacionNodosVecinosColapsoRegion(double val);
        void aplicar(Malla *malla);
        void moverNodosSegunParametro(int ind, double val, Malla *malla){};
	private:
        int indNodo;
        double val;
		int nregionescolapsadas;
		int ntrayectoriasreparadas;
		int repairMalla(Malla *malla);	//Repara la malla de acuerdo a las inconsistencias que se van a producir. Retorna el numero de inconsistencias que encontro.
        double moverHasta(Malla *malla); // mueve la malla una proporcion val de la concentracion de cada nodo, maximo 1.0
		bool checkInterseccionNodo(Malla* malla, int indNodo);	//Chequea si la proyeccion de ese nodo intersecta con el cilindro de proyeccion que lo envuelve.
		bool corrigeInconsistencia (Malla *malla, int indNodo);	//Corrige la inconsistencia. Si no puede, retorna false.
		void colapsarRegion(Malla* malla, int indNodo);
};

#endif
