#include "noverificacion.h"

NoVerificacion::NoVerificacion(double val) : AlgDesplazamientoMallaTriangulos() {
    this->val = val;
}

void NoVerificacion::aplicar(Malla *malla) {
    if(val < 0.0) return;
    malla->moverNodosSegunConcentracion(val);
}
