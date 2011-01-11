#include "guardar.h"

#include "almacenatooff.h"
#include "almacenatoxyzu.h"
#include "almacenatocomsol_1.h"
#include "almacenatomlldebug.h"

Guardar::Guardar(Malla *m, int formato, string filename) : Comando(m) {
    algoritmo=NULL;
	this->filename=filename;
	
	if (formato==0)
		algoritmo = new AlmacenaToOff();
	else if (formato==2)
		algoritmo = new AlmacenaToXYZU();
	else if (formato==3)
		algoritmo = new AlmacenaToComsol_1();
	else if (formato==4)
		algoritmo = new AlmacenaToMllDebug();
	
	assert(algoritmo);
	}

void Guardar::execute() {
    algoritmo->aplicar(malla, filename);
}

Guardar::~Guardar(){
	delete algoritmo;
	}
