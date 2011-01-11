#ifndef GENERAFROMMATLAB_H
#define GENERAFROMMATLAB_H

#include <stdio.h>
#include <string>

#include "alggeneracion.h"
#include "triangulo.h"
#include "cuadrilatero.h"

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
 */
class GeneraFromMatLab : public AlgGeneracion
{
    private:
        string archivo; // nombre del archivo donde estan los datos
        int num_anillos; // número de anillos
        int num_puntos; // númro de puntos por anillo
        int tipo; // tipo de malla. tipo=0 => triangulos. tipo=1 => cuadrilateros.
        Malla* generaMallaTriangulos(); // genera una malla de triangulos del objeto
        Malla* generaMallaCuadrilateros(); // genera una malla de cuadrilateros del objeto
    public:
        GeneraFromMatLab(string arch, int num_anillos=0, int num_puntos=0, int tipo=0);
        Malla* aplicar();
};

#endif
