#include "largoarcomaximo.h"

LargoArcoMaximo::LargoArcoMaximo(double max):Criterio() {
    this->max = max;
}

bool LargoArcoMaximo::seCumple(Malla *malla, int indice) {
	assert (malla->getCara(indice)!=NULL);

 	int arcoMaximo=malla->getCara(indice)->getArcoMasLargo(malla);
	double largoArco=malla->getArco(arcoMaximo)->getLargo(malla);
	if (largoArco>max)
		return false;
	else
		return true;
	}
