#include "nodo.h"

Nodo::Nodo() {
    p = Punto(0,0,0);
    normal = Vect(0,0,0);
    concentracion = 0.0;

    textureX = textureY = 0;
    close1 = close2 = close3 = -1;
    coef1 = coef2 = coef3 = 0;
    original = this;
}

Nodo::Nodo(Punto p) {
    this->p = p;
    normal = Vect(0,0,0);
    concentracion = 0.0;
    textureX = textureY = 0;
    close1 = close2 = close3 = -1;
    coef1 = coef2 = coef3 = 0;
    original = this;
}

Nodo *Nodo::clone() {
	Nodo *nuevo_nodo = new Nodo(this->p);
	nuevo_nodo->setNormal(this->normal);
	nuevo_nodo->setConcentracion(this->concentracion);
	nuevo_nodo->setCaras(this->caras);
	nuevo_nodo->setArcos(this->arcos);
	nuevo_nodo->setTexturePoint(textureX, textureY);
	return nuevo_nodo;
}

void Nodo::setPunto(Punto p) {
    this->p = p;
}

Punto Nodo::getPunto() {
    return p;
}

void Nodo::setNormal(Vect n){
    n.normalizar();
    this->normal=n;
    }

Vect Nodo::getNormal() {
    return normal;
}

void Nodo::setConcentracion(double con) {
    concentracion = con;
}

double Nodo::getConcentracion() {
    return concentracion;
}

void Nodo::setCaras(vector<int> crs) {
    caras = crs;
}

vector<int> Nodo::getCaras() {
    return caras;
}

void Nodo::setArcos(vector<int> ars) {
    arcos = ars;
}

vector<int> Nodo::getArcos() {
    return arcos;
}

void Nodo::addCara(int cara) {
    //si es menor que cero no la agregamos
    if(cara < 0) {
        return;
    }
    //si ya estaba tampoco la agregamos
    for(int i=0; i<(int)caras.size(); i++) {
        if(caras[i] == cara) {
            return;
        }
    }
    caras.push_back(cara);
}

void Nodo::addCaraConRepeticion(int cara) {
    //si es menor que cero no la agregamos
    if(cara < 0) {
        return;
    }
    caras.push_back(cara);
}

void Nodo::eraseCara(int cara) {
    vector<int>::iterator iter;
    for(iter=caras.begin(); iter!=caras.end(); iter++) {
        if(*iter == cara) {
            iter = caras.erase(iter);
            return;
        }
    }
}

bool Nodo::changeCara(int cara_sale, int cara_entra) {
    vector<int>::iterator iter;
    for(iter=caras.begin(); iter!=caras.end(); iter++) {
        if(*iter == cara_sale) {
            *iter = cara_entra;
            return true;
        }
    }
    return false;
}

bool Nodo::changeArco(int arco_sale, int arco_entra) {
    vector<int>::iterator iter;
    for(iter=arcos.begin(); iter!=arcos.end(); iter++) {
        if(*iter == arco_sale) {
            *iter = arco_entra;
            return true;
        }
    }
    return false;
}

void Nodo::addArco(int arco) {
    //si es menor que cero no lo agregamos
    if(arco < 0) {
        return;
    }
    //si ya estaba tampoco lo agregamos
    for(int i=0; i<(int)arcos.size(); i++) {
        if(arcos[i] == arco) {
            return;
        }
    }
    arcos.push_back(arco);
}

void Nodo::eraseArco(int arco) {
    vector<int>::iterator iter;
    vector<double>::iterator iterprob;
    for(iter=arcos.begin(); iter!=arcos.end(); iter++) {
        if(*iter == arco) {
            iter = arcos.erase(iter);
            return;
		}
	}
}

bool Nodo::perteneceAArco(int ind_arco) {
    for(int i = 0; i < (int)arcos.size(); ++i)
        if(arcos[i] == ind_arco)
            return true;
    return false;
}

bool Nodo::perteneceACara(int ind_cara) {
    for(int i = 0; i < (int)caras.size(); ++i)
        if(caras[i] == ind_cara)
            return true;
    return false;
}

string Nodo::imprimir() {
	string aux;
    ostringstream myStream;
    if(this != 0) {
        myStream << "Punto(" << p[0] << "," << p[1] << "," << p[2] << "), normal = " << normal << ", concentracion = " << concentracion << endl;
    }
    else {
        myStream << "Punto nulo" << endl;
    }
    aux = myStream.str();
    cout << aux;
    return aux;
}

void Nodo::setTexturePoint(double p1, double p2){
        this->textureX = p1;
        this->textureY = p2;
}

double Nodo::getTextureX(){
        return textureX;
}

double Nodo::getTextureY(){
        return textureY;
}

float Nodo::distancia(Nodo *n2){
    Punto p1 = getPunto();
    Punto p2 = n2->getPunto();
    float distx = p1.getX() - p2.getX();
    float disty = p1.getY() - p2.getY();
    float distz = p1.getZ() - p2.getZ();
    return (distx*distx) + (disty*disty) + (distz*distz);
}

void Nodo::asociarNodos(int i1, double c1, int i2, double c2, int i3, double c3){
    coef1 = c1;
    coef2 = c2;
    coef3 = c3;
    close1 = i1;
    close2 = i2;
    close3 = i3;
}

int Nodo::getAsociado1(){
    return close1;
}
int Nodo::getAsociado2(){
    return close2;
}
int Nodo::getAsociado3(){
    return close3;
}
double Nodo::getCoef1(){
    return coef1;
}
double Nodo::getCoef2(){
    return coef2;
}
double Nodo::getCoef3(){
    return coef3;
}


Nodo *Nodo::getOriginalNodo(){
        return original;
}

void Nodo::setNewPunto(Punto p){
    if(original == this){
        original = this->clone();
    }
    this->setPunto(p);
}



ostream& operator<<(ostream &os, Nodo *n) {
    if(n != 0) {
        os << "Punto(" << n->p[0] << "," << n->p[1] << "," << n->p[2] << "), normal = " << n->normal << ", concentracion = " << n->concentracion;
    }
    else {
        os << "Punto nulo";
    }
    return os;
}

Nodo::~Nodo(){

	}
