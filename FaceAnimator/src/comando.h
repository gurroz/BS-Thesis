#ifndef COMANDO_H
#define COMANDO_H

#include "malla.h"

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
Esta clase agrupa cada uno de los comandos necesarios en la aplicación.
 */
class Comando {
    protected:
        Malla *malla;
    public:
        Comando(Malla *m);
        Malla* getMalla();
        virtual void execute() = 0;
		virtual ~Comando(){}
};

#endif
