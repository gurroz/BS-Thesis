#ifndef GENERAFROMWFM_H
#define GENERAFROMWFM_H

#include "alggeneracion.h"
#include "triangulo.h"
#include "cuadrilatero.h"

using namespace std;

/**
@author Renato Valenzuela Palominos
Algoritmo que crea una malla a partir de un archivo WFM.
Basado casi íntegramente en generafromcomsol_1.h, de Nicolas Silva Herrera
 */
using namespace std;
class GeneraFromWFM : public AlgGeneracion {
    private:
        string archivo;
    public:
        GeneraFromWFM(string arch);
        Malla* aplicar();
};

#endif
