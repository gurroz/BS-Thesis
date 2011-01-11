#ifndef AREACARA_H
#define AREACARA_H

#include "criterio.h"

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
 */
class AreaCara : public Criterio {
    private:
        double max;
    public:
        AreaCara(double max);
        bool seCumple(Malla *malla, int indice);

};

#endif
