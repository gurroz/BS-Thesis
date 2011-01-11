#ifndef INTERPOLADOR_H
#define INTERPOLADOR_H

#include "malla.h"

/**
@author Renato Valenzuela
*/
class Interpolador{
    public:
        virtual void setearInterpolaciones(Malla *m, Malla *modelo) = 0;
};

#endif
