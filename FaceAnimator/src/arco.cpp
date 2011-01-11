#include "arco.h"
#include "vect.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>

Arco::Arco() {
    nodo1 = -1;
    nodo2 = -1;
    cara1 = -1;
    cara2 = -1;
}

Arco::Arco(int n1, int n2) {
    nodo1 = n1;
    nodo2 = n2;
    cara1 = -1;
    cara2 = -1;
}

Arco::Arco(int n1, int n2, int c1, int c2) {
    nodo1 = n1;
    nodo2 = n2;
    cara1 = c1;
    cara2 = c2;
}

Arco *Arco::clone() {
	return new Arco(this->nodo1,this->nodo2,this->cara1,this->cara2);
}

void Arco::setNodo1(int n1) {
    nodo1 = n1;
}

void Arco::setNodo2(int n2) {
    nodo2 = n2;
}

void Arco::setNodos(int n1, int n2) {
    nodo1 = n1;
    nodo2 = n2;
}

void Arco::setCara1(int c1) {
    cara1 = c1;
}

void Arco::setCara2(int c2) {
    cara2 = c2;
}

void Arco::setCara(int c){
    if(cara1==c || cara2==c)
        return;

    if (cara1==-1)
        cara1=c;
    else if (cara2==-1)
        cara2=c;
    }

void Arco::setCaras(int c1, int c2) {
    cara1 = c1;
    cara2 = c2;
}

bool Arco::changeNodo(int nodo_sale, int nodo_entra) {
	bool cambio = true;
    if(nodo1 == nodo_sale) {
        nodo1 = nodo_entra;
    }
    else if(nodo2 == nodo_sale) {
        nodo2 = nodo_entra;
    }
    else
    	cambio = false;
	return cambio;

}

bool Arco::changeCara(int cara_sale, int cara_entra) {
	bool cambio = true;
    if(cara1 == cara_sale) {
        cara1 = cara_entra;
    }
    else if(cara2 == cara_sale) {
        cara2 = cara_entra;
    }
    else
    	cambio = false;
	return cambio;

}

int Arco::getNodo1() {
    assert(this != 0);
    return nodo1;
}

int Arco::getNodo2() {
    assert(this != 0);
    return nodo2;
}

int Arco::getCara1() {
    assert(this != 0);
    return cara1;
}

int Arco::getCara2() {
    assert(this != 0);
    return cara2;
}

int Arco::getCaraDistinta(int c) {
    assert(c == cara1 || c == cara2);
    int cara = cara1;
    if(cara1 == c)
        cara = cara2;
    return cara;
}

int Arco::getNodoDistinto(int n){
    int resultado = -1;
	if (n==nodo1)
		resultado=nodo2;
	else if (n==nodo2)
		resultado=nodo1;

    assert(resultado>=0);
    return resultado;
	}

bool Arco::estanNodos(vector<int> nodos){
    if (find(nodos.begin(),nodos.end(),nodo1)==nodos.end())
        return false;
    if (find(nodos.begin(),nodos.end(),nodo2)==nodos.end())
        return false;
    return true;
    }

bool Arco::perteneceACara(int ind_cara) {
    return cara1 == ind_cara || cara2 == ind_cara;
}

bool Arco::perteneceNodo(int ind_nodo) {
    return nodo1 == ind_nodo || nodo2 == ind_nodo;
}

double Arco::getLargo(Malla *malla) {
	assert(malla != 0);
	Punto p1 = malla->getNodo(this->getNodo1())->getPunto();
	Punto p2 = malla->getNodo(this->getNodo2())->getPunto();
	double x1 = p1.getX();
	double y1 = p1.getY();
	double z1 = p1.getZ();
	double x2 = p2.getX();
	double y2 = p2.getY();
	double z2 = p2.getZ();
	Vect *v = new Vect(x1-x2,y1-y2,z1-z2);
	double largoArco=v->largo();
	delete v;
	return largoArco;
}

Punto Arco::getPuntoMedio(Malla *malla) {
	assert(malla != 0);
	Punto p1 = malla->getNodo(this->getNodo1())->getPunto();
	Punto p2 = malla->getNodo(this->getNodo2())->getPunto();
	return Punto((p1.getX()+p2.getX())/2,(p1.getY()+p2.getY())/2,(p1.getZ()+p2.getZ())/2);
}

string Arco::imprimir() {
	string aux;
    ostringstream myStream;
    myStream << "Arco: nodos=(" << nodo1 << "," << nodo2 << "); caras=(" << cara1 << "," << cara2 << ")" << endl;
    aux = myStream.str();
    cout << aux;
    return aux;
}

ostream& operator<<(ostream &os, Arco *a) {
	if(a == NULL)
		os << "Arco: NULL";
	else
    	os << "Arco: nodos=(" << a->nodo1 << "," << a->nodo2 << "); caras=(" << a->cara1 << "," << a->cara2 << ")";
    return os;
}
