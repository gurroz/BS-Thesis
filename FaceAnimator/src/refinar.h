#ifndef REFINAR_H
#define REFINAR_H

#include "comando.h"
#include "algrefinamiento.h"

/**
@author Nicolas Silva Herrera
 */
class Refinar : public Comando {
    private:
        AlgRefinamiento *algoritmo;
		Criterio *criterio;
    public:
        Refinar(Malla *m, int algoritmo, int criterio, double valorCriterio);
			//algoritmo=0 => Lepp-Delaunay
			//algoritmo=1 => DelaunayLongestEdgeBisection
	
			//criterio=0 => Angulo Minimo
			//criterio=1 => Area Cara
			//criterio=2 => Largo Arco Maximo
			
        void execute();
		~Refinar();
	
};

#endif
