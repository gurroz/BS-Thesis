#ifndef FABRICAALGORITMOSMALLATRIANGULOS_H
#define FABRICAALGORITMOSMALLATRIANGULOS_H

#include "fabricaalgoritmos.h"

/**
@author Cristina Melo
 */
class FabricaAlgoritmosMallaTriangulos : public FabricaAlgoritmos {
    public:
        FabricaAlgoritmosMallaTriangulos();
    	AlgDesplazamiento *crearAlgoritmoDesplazamiento(int tipo, double val);
    	AlgDesrefinamiento *crearAlgoritmoDesrefinamiento(int tipo);
    	AlgRefinamiento *crearAlgoritmoRefinamiento(int tipo);
    	AlgMejoramiento *crearAlgoritmoMejoramiento(int tipo);
    	vector<string> getAlgoritmosDesplazamiento();
    	vector<string> getAlgoritmosDesrefinamiento();
    	vector<string> getAlgoritmosRefinamiento();
    	vector<string> getAlgoritmosMejoramiento();
    	~FabricaAlgoritmosMallaTriangulos() {};
};

#endif

