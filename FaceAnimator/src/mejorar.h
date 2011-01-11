#ifndef MEJORAR_H
#define MEJORAR_H

#include "comando.h"
#include "algmejoramiento.h"

/**
@author Nicolas Silva Herrera
 */
class Mejorar : public Comando {
    private:
        AlgMejoramiento *algoritmo;
    public:
        Mejorar(Malla *m);
        void execute();
		~Mejorar();
};

#endif
