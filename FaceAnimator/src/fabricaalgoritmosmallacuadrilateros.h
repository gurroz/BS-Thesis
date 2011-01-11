#ifndef FABRICAALGORITMOSMALLACUADRILATEROS_H
#define FABRICAALGORITMOSMALLACUADRILATEROS_H

#include "fabricaalgoritmos.h"

/**
@author Cristina Melo
 */
class FabricaAlgoritmosMallaCuadrilateros : public FabricaAlgoritmos {
    public:
        FabricaAlgoritmosMallaCuadrilateros();
    	AlgDesplazamiento *crearAlgoritmoDesplazamiento(int tipo, double val);
    	AlgDesrefinamiento *crearAlgoritmoDesrefinamiento(int tipo);
    	AlgRefinamiento *crearAlgoritmoRefinamiento(int tipo);
    	AlgMejoramiento *crearAlgoritmoMejoramiento(int tipo);
    	vector<string> getAlgoritmosDesplazamiento();
    	vector<string> getAlgoritmosDesrefinamiento();
    	vector<string> getAlgoritmosRefinamiento();
    	vector<string> getAlgoritmosMejoramiento();
    	~FabricaAlgoritmosMallaCuadrilateros() {};
};

#endif

