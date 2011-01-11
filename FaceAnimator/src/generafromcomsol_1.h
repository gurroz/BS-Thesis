#ifndef GENERAFROMCOMSOL_1_H
#define GENERAFROMCOMSOL_1_H

#include "alggeneracion.h"
#include "triangulo.h"
#include "cuadrilatero.h"

using namespace std;

/**
@author Nicolas Silva Herrera
Algoritmo que crea una malla a partir de un archivo Comsol_1.
 */
using namespace std;
class GeneraFromComsol_1 : public AlgGeneracion {
    private:
        string archivo;
    public:
        GeneraFromComsol_1(string arch);
        Malla* aplicar();
};

#endif
