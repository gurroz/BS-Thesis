#ifndef GENERAFROMWRL_H
#define GENERAFROMWRL_H

#include <stdio.h>

#include <map>
#include <math.h>
#include <string>
#include <fstream>

#include "alggeneracion.h"
#include "triangulo.h"
#include "cuadrilatero.h"

using namespace std;

/**
@author Renato Valenzuela Palominos
Algoritmo que crea una malla a partir de un archivo WRL.
 */
class GeneraFromWRL : public AlgGeneracion {
    private:
        string archivo;
        Malla *getMallaFromFile(ifstream *in);
    public:
        GeneraFromWRL(string arch);
        Malla* aplicar();
};

#endif
