#include "informar.h"

Informar::Informar(Malla *m) : Comando(m) {
    this->algoritmo = NULL;
	
	this->algoritmo=new InformacionMalla();
	
	assert(algoritmo);
	}

void Informar::execute() {
    algoritmo->aplicar(malla);
	}

double* Informar::getInfo(){
	return algoritmo->getInfo();
	}

double Informar::getLimiteMenorHistograma(int bin){
	return algoritmo->getLimiteMenorHistograma(bin);
	}

double Informar::getLimiteMayorHistograma(int bin){
	return algoritmo->getLimiteMayorHistograma(bin);
	}

double Informar::getFrecuenciaHistograma(int bin){
	return algoritmo->getFrecuenciaHistograma(bin);
	}
	
Informar::~Informar(){
	delete algoritmo;
	}
