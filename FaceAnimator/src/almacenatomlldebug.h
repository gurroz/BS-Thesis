#ifndef ALMACENATOMLLDEBUG_H
#define ALMACENATOMLLDEBUG_H

#include "algalmacenamiento.h"

/**
@author Nicolas Silva Herrera
 */
class AlmacenaToMllDebug : public AlgAlmacenamiento {
    public:
        AlmacenaToMllDebug();
        void aplicar(Malla *malla, string filename);
};

#endif
