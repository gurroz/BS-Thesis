#include "desrefinar.h"

#include "desrefinamientoedgecollapse.h"
#include "areacara.h"
#include "largoarcominimo.h"
#include "fabricaalgoritmos.h"

Desrefinar::Desrefinar(Malla *m, int algoritmo, int criterio, double valorCriterio): Comando(m) {
    assert(m);

	this->algoritmo=NULL;
	this->criterio=NULL;

	FabricaAlgoritmos *fabrica = m->getFabricaAlgoritmos();

	this->algoritmo=fabrica->crearAlgoritmoDesrefinamiento(algoritmo);

	if (criterio==1)
		this->criterio=new AreaCara(valorCriterio);
	else if (criterio==2)
		this->criterio=new LargoArcoMinimo(valorCriterio);

	assert(this->algoritmo && this->criterio);
	}

void Desrefinar::execute() {
    algoritmo->aplicar(malla,criterio);
	}

Desrefinar::~Desrefinar(){
	delete algoritmo;
	delete criterio;
	}
