#ifndef REGISTRATIONMETHOD_H_INCLUDED
#define REGISTRATIONMETHOD_H_INCLUDED

#include "malla.h"

class RegistrationMethod{
  public:
        virtual bool execute(Malla *malla, Malla *modelo) = 0;


};


#endif // REGISTRATIONMETHOD_H_INCLUDED
