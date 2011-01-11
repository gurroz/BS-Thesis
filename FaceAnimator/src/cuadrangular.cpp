#include "cuadrangular.h"

#include "mallatriangulos.h"

Cuadrangular::Cuadrangular(Malla *m, AlgCentroTriangulo *a) : Comando(m) {
	assert(m->getTipoMalla() == "triangular");
    this->algoritmo = a;
	assert(a);
	}

void Cuadrangular::execute() {
	nueva_malla = ((MallaTriangulos *)malla)->cuadrangular(algoritmo);
}

MallaCuadrilateros *Cuadrangular::getMalla() {
	return nueva_malla;
}
Cuadrangular::~Cuadrangular(){
	delete algoritmo;
	}
