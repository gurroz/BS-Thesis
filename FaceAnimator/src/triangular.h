#ifndef TRIANGULAR_H
#define TRIANGULAR_H

#include "comando.h"
#include "mallatriangulos.h"

/**
@author Cristina Melo
*/
class Triangular : public Comando {
	private:
		MallaTriangulos *nueva_malla;
    public:
        Triangular(Malla *m);
        void execute();
        MallaTriangulos *getMalla();
		~Triangular();
};

#endif
