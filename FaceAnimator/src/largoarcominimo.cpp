#include "largoarcominimo.h"

LargoArcoMinimo::LargoArcoMinimo(double max):Criterio() {
    this->max = max;
}

bool LargoArcoMinimo::seCumple(Malla *malla, int indice) {
	assert (malla->getCara(indice)!=NULL);

    int arcoMinimo=malla->getCara(indice)->getArcoMasCorto(malla);
	double largoArco=malla->getArco(arcoMinimo)->getLargo(malla);
	if (largoArco>max)
		return false;
	else
		return true;
	}

