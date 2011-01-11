#ifndef DEFORMAR_H
#define DEFORMAR_H

#include "comando.h"
#include "algdesplazamiento.h"

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
*/
class Deformar : public Comando {
    private:
        AlgDesplazamiento *algoritmo;
    public:
        Deformar(Malla *m, int tipoVerificaciones, double porcentajeAMover=-1);
			//tipoVerificaciones=0 => No verificacion
			//tipoVerificaciones=1 => Consistencia local
			//tipoVerificaciones=2 => Verificacion por nodos vecinos.
			//tipoVerificaciones=3 => Verificacion por nodos vecinos colapsando región.
        void execute();
		~Deformar();
};

#endif
