#ifndef GENERAR_H
#define GENERAR_H

#include "comando.h"
#include "malla.h"
#include "alggeneracion.h"
#include "interpolador.h"
#include "registrationmethod.h"

#include <string>
#include <list>

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
 */
using namespace std;
class GenerarMallaInicial : public Comando {
    private:
        AlgGeneracion *algoritmo;
    public:
	    GenerarMallaInicial (int tipoFiltro, list<string> filenames, int numeroDeAnillos=-1, int puntosPorAnillo=-1, int tipoMalla=-1);
			//tipoFiltro=0 => Off (Geomview)
			//tipoFiltro=1 => txt (Matlab)
			//tipoFiltro=2 => nxnynzu
			//tipoFiltro=3 => comsol
			//tipoFiltro=4 => wfm
			//tipoFiltro=5 => wrl
		GenerarMallaInicial (int tipo, int altura, int radio, int numeroDeAnillos, int puntosPorAnillo, int tipoMalla);
			//tipo=10 => Cilindro
        GenerarMallaInicial(int tipo, string filename, int radio, int numeroDeAnillos, int puntosPorAnillo, int tipoMalla);
            //tipo=20 => Generar desde medula
		void execute();
		~GenerarMallaInicial();
};

#endif
