#ifndef GENERAFROMMEDULA_H
#define GENERAFROMMEDULA_H

#include "alggeneracion.h"
#include "triangulo.h"
#include "cuadrilatero.h"

//Genera una malla de arbol desde un archivo que indica su medula.
//Nota: Solo admite medulas que sean estrictamente crecientes en el eje y.

class GeneraFromMedula : public AlgGeneracion
{
    public:
        GeneraFromMedula(string archivo, double radio=1, int num_anillos=20, int num_puntos=10, int tipoMalla=0);
        Malla* aplicar();
        ~GeneraFromMedula();
    protected:
    private:
        Nodos* nodos;
        Arcos* arcos;
        Caras* caras;
        vector<Punto> medula;
        double radio; // radio del cilindro
        int num_anillos; // número de anillos del cilindro
        int num_puntos; // número de puntos por cada anillo del cilindro
        int tipo_malla; // 0 => triángulos, 1 0 => cuadriláteros
        void updateVecinos();   //Actualiza los vecinos de los elementos de la malla
        void generarNodos(); // genera los nodos y los setea
        Malla *generaMallaTriangulos(); // genera una malla de triangulos a partir de la malla
        Malla *generaMallaCuadrilateros(); // genera una malla de cuadrilateros a partir de la malla

        Punto* sectorMedula(double altura); //Retorna el punto central del cilindro en la pos y=altura
};



#endif // GENERAFROMMEDULA_H
