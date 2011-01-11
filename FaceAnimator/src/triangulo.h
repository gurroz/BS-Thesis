#ifndef TRIANGULO_H
#define TRIANGULO_H

#include <cassert>
#include "cara.h"
#include <vector>

using namespace std;

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
Esta clase representa una cara del objeto a modelar. Posee una lista de indices a los puntos que
forman la cara, y una lista de indices a los arcos que forman la cara.
 */
class Triangulo: public Cara {
    public:
        Triangulo(int n1, int n2, int n3, int a1, int a2, int a3); // crea una cara con 3 elementos --> un triángulo
        Triangulo(int n1, int n2, int n3);
        Cara *clone();
        Triangulo(vector<int> ind_pts, vector<int> ind_arcs); // crea una cara con la lista de índices dados
        int getPuntoDistinto(int p1, int p2); // solo para una cara triangular, retorna el indice que es distinto a los indices pasados como parametros.
        string getEtiqueta(); // indica que la cara es de tipo "triangular"
        Cara *colapsarArco(Malla *malla, int ind_arco, int ind_nodo); // Colapsa un arco del triangulo, por lo que la cara resultante es nula
};

#endif
