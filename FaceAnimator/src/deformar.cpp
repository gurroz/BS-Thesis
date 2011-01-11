#include "deformar.h"

#include "noverificacion.h"
#include "verificacionlocal.h"
#include "verificacionnodosvecinos.h"
#include "verificacionnodosvecinoscolapsoregion.h"
#include "fabricaalgoritmos.h"

Deformar::Deformar(Malla *m, int tipoVerificaciones, double porcentajeAMover) : Comando(m) {
    this->algoritmo = NULL;

    FabricaAlgoritmos *fabrica = m->getFabricaAlgoritmos();
    this->algoritmo = fabrica->crearAlgoritmoDesplazamiento(tipoVerificaciones, porcentajeAMover);

	assert(algoritmo);
	}

void Deformar::execute() {
    algoritmo->aplicar(malla);
	}

Deformar::~Deformar(){
	delete algoritmo;
	}
