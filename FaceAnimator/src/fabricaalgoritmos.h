#ifndef FABRICAALGORITMOS_H
#define FABRICAALGORITMOS_H

#include "algdesplazamiento.h"
#include "algdesrefinamiento.h"
#include "algrefinamiento.h"
#include "algmejoramiento.h"

/**
@author Cristina Melo
 */

class AlgDesplazamiento;
class AlgRefinamiento;
class AlgDesrefinamiento;
class AlgMejoramiento;

class FabricaAlgoritmos {
    public:
    	virtual AlgDesplazamiento *crearAlgoritmoDesplazamiento(int tipo, double val) = 0;
    	virtual AlgDesrefinamiento *crearAlgoritmoDesrefinamiento(int tipo) = 0;
    	virtual AlgRefinamiento *crearAlgoritmoRefinamiento(int tipo) = 0;
    	virtual AlgMejoramiento *crearAlgoritmoMejoramiento(int tipo) = 0;
    	virtual vector<string> getAlgoritmosDesplazamiento() = 0;
    	virtual vector<string> getAlgoritmosDesrefinamiento() = 0;
    	virtual vector<string> getAlgoritmosRefinamiento() = 0;
    	virtual vector<string> getAlgoritmosMejoramiento() = 0;
    	virtual ~FabricaAlgoritmos() {};
};

#endif
