#include "triangulo.h"

Triangulo::Triangulo(int n1, int n2, int n3, int a1, int a2, int a3) {
    num_elem = 3;
    ind_nodos.push_back(n1);
    ind_nodos.push_back(n2);
    ind_nodos.push_back(n3);
    ind_arcos.push_back(a1);
    ind_arcos.push_back(a2);
    ind_arcos.push_back(a3);
    rgb[0] = -1;
    rgb[1] = -1;
    rgb[2] = -1;
}

Triangulo::Triangulo(int n1, int n2, int n3) {
    num_elem = 3;
    ind_nodos.push_back(n1);
    ind_nodos.push_back(n2);
    ind_nodos.push_back(n3);
    rgb[0] = -1;
    rgb[1] = -1;
    rgb[2] = -1;
}

Triangulo::Triangulo(vector<int> ind_nds, vector<int> ind_arcs):Cara(ind_nds,ind_arcs) {
    assert(ind_nds.size() == ind_arcs.size() && ind_arcs.size() == 3);
}

Cara *Triangulo::clone() {
	Triangulo *nuevo_triangulo = new Triangulo(ind_nodos, ind_arcos);
	nuevo_triangulo->setColores(rgb[0],rgb[1],rgb[2]);
	return nuevo_triangulo;
}

int Triangulo::getPuntoDistinto(int p1, int p2) {
    assert(num_elem == 3);
    if(ind_nodos[0] != p1 && ind_nodos[0] != p2) {
        return ind_nodos[0];
    }
    else if(ind_nodos[1] != p1 && ind_nodos[1] != p2) {
        return ind_nodos[1];
    }
    else {
        return ind_nodos[2];
    }
}

Cara *Triangulo::colapsarArco(Malla *malla, int ind_arco, int ind_nodo) {
    return NULL;
}

string Triangulo::getEtiqueta() {
    return "triangular";
}
