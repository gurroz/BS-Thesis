#ifndef INTERPOLADORNODOSCERCANOS_H_INCLUDED
#define INTERPOLADORNODOSCERCANOS_H_INCLUDED

#include "interpolador.h"

class InterpoladorNodosCercanos : public Interpolador
{
    public:
        InterpoladorNodosCercanos();
        void setearInterpolaciones(Malla *m, Malla *modelo);
        ~InterpoladorNodosCercanos();

};


#endif // INTERPOLADORNODOSCERCANOS_H_INCLUDED
