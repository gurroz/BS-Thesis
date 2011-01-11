#include "areacara.h"

AreaCara::AreaCara(double max):Criterio() {
    this->max = max;
}

bool AreaCara::seCumple(Malla *malla, int indice) {
	assert (malla->getCara(indice)!=NULL);

    double area_cara = malla->getCara(indice)->getArea(malla);
    if(area_cara > max) {
        return false;
    }
    else {
        return true;
    }
}
