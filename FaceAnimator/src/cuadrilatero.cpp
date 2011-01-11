#include "cuadrilatero.h"
#include "triangulo.h"

Cuadrilatero::Cuadrilatero(int n1, int n2, int n3, int n4, int a1, int a2, int a3, int a4) {
    num_elem = 4;
    ind_nodos.push_back(n1);
    ind_nodos.push_back(n2);
    ind_nodos.push_back(n3);
    ind_nodos.push_back(n4);
    ind_arcos.push_back(a1);
    ind_arcos.push_back(a2);
    ind_arcos.push_back(a3);
    ind_arcos.push_back(a4);
    rgb[0] = -1;
    rgb[1] = -1;
    rgb[2] = -1;
}

Cuadrilatero::Cuadrilatero(int n1, int n2, int n3, int n4) {
    num_elem = 4;
    ind_nodos.push_back(n1);
    ind_nodos.push_back(n2);
    ind_nodos.push_back(n3);
    ind_nodos.push_back(n4);
    rgb[0] = -1;
    rgb[1] = -1;
    rgb[2] = -1;
}

Cuadrilatero::Cuadrilatero(vector<int> ind_nds, vector<int> ind_arcs):Cara(ind_nds,ind_arcs) {
    assert(ind_nds.size() == ind_arcs.size() && ind_nds.size() == 4);
}

Cara *Cuadrilatero::clone() {
	Cuadrilatero *nuevo_cuadrilatero = new Cuadrilatero(ind_nodos, ind_arcos);
	nuevo_cuadrilatero->setColores(rgb[0],rgb[1],rgb[2]);
	return nuevo_cuadrilatero;
}

Cara *Cuadrilatero::colapsarArco(Malla *malla, int ind_arco, int ind_nodo) {
    vector<int> nuevos_nodos;
    vector<int> nuevos_arcos;
    int otro_nodo = malla->getArco(ind_arco)->getNodoDistinto(ind_nodo);
    for(int i = 0; i < num_elem; ++i) {
        if(ind_nodos[i] != ind_nodo)
            nuevos_nodos.push_back(ind_nodos[i]);
        Arco *arco = malla->getArco(ind_arcos[i]);
        if(ind_arcos[i] != ind_arco) {
            nuevos_arcos.push_back(ind_arcos[i]);
            if(arco->perteneceNodo(ind_nodo) && ind_arcos[i] != ind_arco) // El otro arco del nodo
                arco->changeNodo(ind_nodo,otro_nodo);
        }
    }
    malla->getNodo(otro_nodo)->eraseArco(ind_arco);
    return new Triangulo(nuevos_nodos,nuevos_arcos);;
}

string Cuadrilatero::getEtiqueta() {
    return "quadrilateral";
}
