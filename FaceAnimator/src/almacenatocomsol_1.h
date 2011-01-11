#ifndef ALMACENATOCOMSOL_1_H
#define ALMACENATOCOMSOL_1_H

#include "algalmacenamiento.h"

/**
@author Nicolas Silva Herrera
 */
class AlmacenaToComsol_1 : public AlgAlmacenamiento {
    public:
        AlmacenaToComsol_1();
        void aplicar(Malla *malla, string filename);
};

#endif
