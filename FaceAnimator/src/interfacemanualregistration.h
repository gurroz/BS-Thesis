#ifndef INTERFACEMANUALREGISTRATION_H_INCLUDED
#define INTERFACEMANUALREGISTRATION_H_INCLUDED


#include "registrationmethod.h"

class InterfaceManualRegistration: public RegistrationMethod{
    public:
        bool execute(Malla *malla, Malla *modelo);
};


#endif // INTERFACEMANUALREGISTRATION_H_INCLUDED
