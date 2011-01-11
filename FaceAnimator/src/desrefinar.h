#ifndef DESREFINAR_H
#define DESREFINAR_H

#include "comando.h"
#include "algdesrefinamiento.h"

/**
@author Nicolas Silva Herrera
 */
class Desrefinar : public Comando {
    private:
        AlgDesrefinamiento *algoritmo;
		Criterio *criterio;
    public:
        Desrefinar(Malla *m, int algoritmo, int criterio, double valorCriterio);
			//algoritmo=0 => Desrefinamiento por Edge Collapse
	
			//criterio=1 => Area Cara
			//criterio=2 => Largo Arco Minimo
			
        void execute();
		~Desrefinar();
	
};

#endif
