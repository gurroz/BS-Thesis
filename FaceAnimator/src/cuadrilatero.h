#ifndef CUADRILATERO_H
#define CUADRILATERO_H

#include <cassert>
#include "cara.h"
#include <vector>

using namespace std;

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
Esta clase representa una cara del objeto a modelar. Posee una lista de indices a los puntos que
forman la cara, y una lista de indices a los arcos que forman la cara.
 */
class Cuadrilatero: public Cara {
    public:
        Cuadrilatero(int n1, int n2, int n3, int n4, int a1, int a2, int a3, int a4); // crea una cara con 4 elementos
        Cuadrilatero(int n1, int n2, int n3, int n4);
        Cuadrilatero(vector<int> ind_pts, vector<int> ind_arcs); // crea una cara con la lista de índices dados
        Cara *clone();
        string getEtiqueta(); // indica que la cara es de tipo "quadrilateral"
        Cara *colapsarArco(Malla *malla, int ind_arco, int ind_nodo); // Colapsa un arco del cuadrilatero, borrando un nodo, retorna el triangulo resultante

};

#endif
