#ifndef INTERPOLADORMIXTO_H_INCLUDED
#define INTERPOLADORMIXTO_H_INCLUDED

#include "interpolador.h"

class InterpoladorMixto : public Interpolador
{
    public:
        InterpoladorMixto();
        void setearInterpolaciones(Malla *m, Malla *modelo);
        ~InterpoladorMixto();

};


#endif // INTERPOLADORMIXTO_H_INCLUDED
