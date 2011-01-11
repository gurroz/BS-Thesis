#include "triangular.h"

#include "mallacuadrilateros.h"

Triangular::Triangular(Malla *m) : Comando(m) {
	assert(m->getTipoMalla() == "quadrilateral");
	}

void Triangular::execute() {
	nueva_malla = ((MallaCuadrilateros *)malla)->triangular();
	}

MallaTriangulos *Triangular::getMalla() {
	return nueva_malla;
}
Triangular::~Triangular(){
}
