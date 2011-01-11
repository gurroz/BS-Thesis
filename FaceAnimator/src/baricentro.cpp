#include "baricentro.h"
#include "vect.h"

Baricentro::Baricentro(Malla *malla):AlgCentroTriangulo(malla) {
}

Punto Baricentro::getCentro(Triangulo *triangulo) {
	vector<int> nodos = triangulo->getNodos();
	Vect v_centro;
	int n = triangulo->getNumElem();
	for(int i = 0; i < n; ++i)
		v_centro = v_centro + Vect(_malla->getNodo(nodos[i])->getPunto());
	v_centro = v_centro * (1.0 / n);
	return v_centro.getPunto();
}

double Baricentro::getConcentracionCentro(Triangulo *triangulo) {
	vector<int> nodos = triangulo->getNodos();
	double concentracion = 0;
	int n = triangulo->getNumElem();
	for(int i = 0; i < n; ++i)
		concentracion += _malla->getNodo(nodos[i])->getConcentracion();
	concentracion /= n;
	return concentracion;
}


