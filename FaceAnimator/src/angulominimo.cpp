#include "angulominimo.h"

AnguloMinimo::AnguloMinimo(double min) : Criterio() {
    this->min = min;
}

bool AnguloMinimo::seCumple(Malla *malla, int indice) {
	assert (malla->getCara(indice)!=NULL);

    double angulo_min = malla->getCara(indice)->getAnguloMin(malla);
    if(angulo_min < min) {
        return false;
    }
    else {
        return true;
    }
}
