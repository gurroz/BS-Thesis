#include "refinar.h"

#include "leppdelaunay.h"
#include "delaunaylongestedgebisection.h"
#include "angulominimo.h"
#include "areacara.h"
#include "largoarcomaximo.h"
#include "fabricaalgoritmos.h"

Refinar::Refinar(Malla *m, int algoritmo, int criterio, double valorCriterio): Comando(m) {
    assert(m);

	this->algoritmo=NULL;
	this->criterio=NULL;

	FabricaAlgoritmos *fabrica = m->getFabricaAlgoritmos();
	this->algoritmo=fabrica->crearAlgoritmoRefinamiento(algoritmo);

	if (criterio==0)
		this->criterio=new AnguloMinimo(valorCriterio);
	else if (criterio==1)
		this->criterio=new AreaCara(valorCriterio);
	else if (criterio==2)
		this->criterio=new LargoArcoMaximo(valorCriterio);

	assert(this->algoritmo && this->criterio);
	}

void Refinar::execute() {
    algoritmo->aplicar(malla,criterio);
	}

Refinar::~Refinar(){
	delete algoritmo;
	delete criterio;
	}
