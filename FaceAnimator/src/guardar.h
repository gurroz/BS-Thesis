#ifndef GUARDAR_H
#define GUARDAR_H

#include "comando.h"
#include "algalmacenamiento.h"

/**
@author Nicolas Silva Herrera
 */
class Guardar : public Comando {
    private:
        AlgAlmacenamiento *algoritmo;
		string filename;
    public:
        Guardar(Malla *m, int formato, string filename);
			//formato=0 => Geomview
			//formato=2 => nxnynzu
			//formato=3 => comsol
			//formato=4 => mlldebug
        void execute();
		~Guardar();
};

#endif
