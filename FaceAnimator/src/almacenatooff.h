#ifndef ALMACENATOOFF_H
#define ALMACENATOOFF_H

#include "algalmacenamiento.h"

/**
@author Nicolas Silva Herrera
 */
class AlmacenaToOff : public AlgAlmacenamiento {
    public:
        AlmacenaToOff();
        void aplicar(Malla *malla, string filename);
};

#endif
