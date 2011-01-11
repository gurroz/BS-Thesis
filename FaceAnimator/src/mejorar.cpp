#include "mejorar.h"

#include "mejdelaunay.h"
#include "fabricaalgoritmos.h"

Mejorar::Mejorar(Malla *m) : Comando(m) {
    FabricaAlgoritmos *fabrica = m->getFabricaAlgoritmos();
    algoritmo = fabrica->crearAlgoritmoMejoramiento(0);
}

void Mejorar::execute() {
    algoritmo->aplicar(malla);
}

Mejorar::~Mejorar(){
	delete algoritmo;
	}
