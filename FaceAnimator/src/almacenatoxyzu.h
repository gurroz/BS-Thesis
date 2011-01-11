#ifndef ALMACENATOXYZU_H
#define ALMACENATOXYZU_H

#include "algalmacenamiento.h"

/**
@author Nicolas Silva Herrera
 */
class AlmacenaToXYZU : public AlgAlmacenamiento {
    public:
        AlmacenaToXYZU();
        void aplicar(Malla *malla, string filename);
};

#endif
