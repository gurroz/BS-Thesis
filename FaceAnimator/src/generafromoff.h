#ifndef GENERAFROMOFF_H
#define GENERAFROMOFF_H

#include <stdio.h>

#include <map>
#include <math.h>
#include <string>

#include "alggeneracion.h"
#include "triangulo.h"
#include "cuadrilatero.h"

using namespace std;

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
Algoritmo que crea una malla a partir de un archivo OFF de Geomview.
 */
class GeneraFromOFF : public AlgGeneracion {
    private:
        string archivo;
    public:
        GeneraFromOFF(string arch);
        Malla* aplicar();
};

#endif
