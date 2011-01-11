#include "malla.h"

#include "adaptercomputationalgeometry.h"

#include "movimientosFromFile.h"
#include <limits>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>

/*** CONSTRUCTORES: ***/
Malla::Malla(Punto p0, Punto p1) {
	nodos = new Nodos();
	arcos = new Arcos();
	caras = new Caras();
	arcos->addArco(new Arco(nodos->addNodo(new Nodo(p0)),nodos->addNodo(new Nodo(p1)),-1,-1));
	show_nodos_destacados=true;
	concentracion_max = 1;
	concentracion_min = 0;
	fabrica_algoritmos = NULL;
	hasTextura = false;
	sgteMalla = NULL;
}

Malla::Malla(Nodos *nds, Arcos *arcs, Caras *crs) {
	nodos = nds;
	arcos = arcs;
	caras = crs;
	show_nodos_destacados = true;
	concentracion_max = 1;
	concentracion_min = 0;
	fabrica_algoritmos = NULL;
	hasTextura = false;
	sgteMalla = NULL;
}


/*** SETTERS Y GETTERS: ***/
void Malla::setConcentracionMax(double max) {
	concentracion_max = max;
}

void Malla::setConcentracionMin(double min) {
	concentracion_min = min;
}

double Malla::getConcentracionMax() {
	return concentracion_max;
}

double Malla::getConcentracionMin() {
	return concentracion_min;
}

Nodos* Malla::getNodos(){
    return nodos;
}

Nodo* Malla::getNodo(int ind_nodo) {
	return nodos->getNodo(ind_nodo);
}

Arco* Malla::getArco(int ind_arco) {
	return arcos->getArco(ind_arco);
}

Cara* Malla::getCara(int ind_cara) {
	return caras->getCara(ind_cara);
}

int Malla::getMaxIndiceNodos() {
	return nodos->getNumNodos() -1;
}

int Malla::getMaxIndiceArcos() {
	return arcos->getNumArcos() -1;
}

int Malla::getMaxIndiceCaras() {
	return caras->getNumCaras() -1;
}

int Malla::getNumNodos() {
	return nodos->getNumNodosValidos();
}

int Malla::getNumArcos() {
	return arcos->getNumArcosValidos();
}

int Malla::getNumCaras() {
	return caras->getNumCarasValidas();
}

void Malla::setNodoDestacado(int indNodo){
	nodosDestacados.push_back(indNodo);
	}

vector<int>* Malla::getNodosDestacados(){
	return &nodosDestacados;
	}

void Malla::clearNodosDestacados(){
	nodosDestacados.clear();
	}

void Malla::setMedula(vector<Punto> medula){
	this->medula=medula;
	}

vector<Punto> Malla::getMedula(){
	return this->medula;
	}

FabricaAlgoritmos *Malla::getFabricaAlgoritmos() {
    return NULL;
}

void Malla::setTextura(GLuint b){
    textura = b;
    hasTextura = true;
}

GLuint Malla::getTextura(){
    if(hasTextura == false)
        cout << "Error: Obteniendo textura de malla sin textura."<< endl;
    return textura;
}

bool Malla::tieneTextura(){
    return hasTextura;
}

void Malla::setMovimientos(string file){
	movimientos = new MovimientosFromFile(file);
}


/*** MÉTODOS ARCOS: ***/
double Malla::getAnguloArco(int ind_arco) {
	assert((ind_arco < arcos->getNumArcos()) && (ind_arco >= 0));

	int ind_c1 = arcos->getArco(ind_arco)->getCara1();
	int ind_c2 = arcos->getArco(ind_arco)->getCara2();

	Vect normal_c1 = caras->getCara(ind_c1)->getNormal(this);
	Vect normal_c2 = caras->getCara(ind_c2)->getNormal(this);

	return normal_c1.getAngulo(normal_c2);
}

bool Malla::esArcoBorde(int ind_arco) {
	assert((ind_arco < arcos->getNumArcos()) && (ind_arco >= 0));

	int ind_c1 = arcos->getArco(ind_arco)->getCara1();
	int ind_c2 = arcos->getArco(ind_arco)->getCara2();

	if(ind_c1 == -1 || ind_c2 == -1) {
		//cout << "Arco " << ind_arco << " es de borde." << endl;
		return true;
	}
	return false;
}

bool Malla::esAnguloDiedro(int ind_arco, double anguloDiedroMax) {
	assert((ind_arco < arcos->getNumArcos()) && (ind_arco >= 0));

	double anguloDiedro = this->getAnguloArco(ind_arco);
	if(anguloDiedro > anguloDiedroMax) {
		// No se puede realizar flip porque se pierde la forma.
		return true;
	}

	//Finalmente retornamos falso.
	return false;
}

bool Malla::esArcoConcavo(int ind_arco) {
	assert((ind_arco < arcos->getNumArcos()) && (ind_arco >= 0));

	int ind_c1 = arcos->getArco(ind_arco)->getCara1();
	int ind_c2 = arcos->getArco(ind_arco)->getCara2();

	if(ind_c1 == -1 || ind_c2 == -1) {
		return false;
	}

	Cara *c1 = caras->getCara(ind_c1);
	Cara *c2 = caras->getCara(ind_c2);

	//obtenemos los indices de los puntos
	int ind_p1 = arcos->getArco(ind_arco)->getNodo1();
	int ind_p2 = arcos->getArco(ind_arco)->getNodo2();

	double angulo1 = c1->getAnguloVertice(ind_p1,this) + c2->getAnguloVertice(ind_p1,this);
	double angulo2 = c1->getAnguloVertice(ind_p2,this) + c2->getAnguloVertice(ind_p2,this);

	//si se forma un angulo mayor o igual a 180º no se puede realizar el flip
	if(angulo1 >= PI || angulo2 >= PI) {
		//Es concavo
		return true;
	}

	//Finalmente retornamos falso. es convexo
	return false;
}

bool Malla::esArcoFijo(int ind_arco) {
	assert((ind_arco < arcos->getNumArcos()) && (ind_arco >= 0));
	if(esArcoBorde(ind_arco)) {
		return true;
	}
	if(esAnguloDiedro(ind_arco,ANGULO_DIEDRO)) {
		return true;
	}
	if(esArcoConcavo(ind_arco)) {
		return true;
	}
	return false;
}

/*** MÉTODOS NODOS: ***/
bool Malla::esNodoBorde(int indNodo){
	vector<int> arcos=getNodo(indNodo)->getArcos();
	for (int i=0; i<(int)arcos.size(); i++)
		if (esArcoBorde(arcos[i]))
			return true;

	return false;
	}

bool Malla::esNodoBordeSuperior(int ind_nodo) {
	if (!esNodoBorde(ind_nodo))
		return false;

	vector<int> arcosvecinos=nodos->getNodo(ind_nodo)->getArcos();
	int ind_nodo_distinto;
	for (int i=0; i<(int)arcosvecinos.size(); i++){
		if (!esArcoBorde(arcosvecinos[i])){
			ind_nodo_distinto=arcos->getArco(arcosvecinos[i])->getNodoDistinto(ind_nodo);
			if (nodos->getNodo(ind_nodo)->getPunto().getY() < nodos->getNodo(ind_nodo_distinto)->getPunto().getY())
				return false;
			}
		}
	return true;
	}

bool Malla::esNodoBordeInferior(int ind_nodo) {
	if (!esNodoBorde(ind_nodo))
		return false;

	vector<int> arcosvecinos=nodos->getNodo(ind_nodo)->getArcos();
	int ind_nodo_distinto;
	for (int i=0; i<(int)arcosvecinos.size(); i++){
		if (!esArcoBorde(arcosvecinos[i])){
			ind_nodo_distinto=arcos->getArco(arcosvecinos[i])->getNodoDistinto(ind_nodo);
			if (nodos->getNodo(ind_nodo)->getPunto().getY() > nodos->getNodo(ind_nodo_distinto)->getPunto().getY())
				return false;
			}
		}
	return true;
	}

/*** MÉTODOS CARAS: ***/
double Malla::getAnguloCaras(int ind_cara1, int ind_cara2) {
	assert((ind_cara1 < caras->getNumCaras()) && (ind_cara1 >= 0));
	assert((ind_cara2 < caras->getNumCaras()) && (ind_cara2 >= 0));
	Vect v1 = caras->getCara(ind_cara1)->getNormal(this);
	Vect v2 = caras->getCara(ind_cara2)->getNormal(this);
	return v1.getAngulo(v2);
}

bool Malla::sonCarasVecinas(int ind_cara1, int ind_cara2) {
	assert((ind_cara1 < caras->getNumCaras()) && (ind_cara1 >= -1));
	assert((ind_cara2 < caras->getNumCaras()) && (ind_cara2 >= -1));

	if(ind_cara1 == -1 || ind_cara2 == -1) {
		return false;
	}
	vector<int> arcos_cara1 = this->caras->getCara(ind_cara1)->getArcos();
	vector<int> arcos_cara2 = this->caras->getCara(ind_cara2)->getArcos();
	for(int i=0; i<(int)arcos_cara1.size(); i++) {
		for(int j=0; j<(int)arcos_cara2.size(); j++) {
			if(arcos_cara1[i] == arcos_cara2[j]) {
				return true;
			}
		}
	}
	return false;
}

bool Malla::esCaraBorde(int ind_cara) {
	assert((ind_cara < caras->getNumCaras()) && (ind_cara >= 0));
	vector<int> ind_arcos_cara = caras->getCara(ind_cara)->getArcos();
	for(int i=0; i<(int)ind_arcos_cara.size(); i++) {
		if(esArcoBorde(ind_arcos_cara[i])) {
			return true;
		}
	}
	return false;
}

vector<int> Malla::getArcosBordeCara(int ind_cara) {
	assert((ind_cara < caras->getNumCaras()) && (ind_cara >= 0));
	vector<int> arcos_borde;
	vector<int> ind_arcos_cara = caras->getCara(ind_cara)->getArcos();
	for(int i=0; i<(int)ind_arcos_cara.size(); i++) {
		if(esArcoBorde(ind_arcos_cara[i])) {
			arcos_borde.push_back(ind_arcos_cara[i]);
		}
	}
	return arcos_borde;
}

bool Malla::existeCaminoEntre(int n1, int n2){
    Nodo *nodo2 = getNodo(n2);

    int nodo_elegido = -1;
    std::set<int> nodos_usados;
    for(int nn = n1; nn != n2; nn = nodo_elegido){
        nodos_usados.insert(nn);
        double distancia_inicial = getNodo(nn)->distancia(nodo2);
        vector<int> arcs = getNodo(nn)->getArcos();
        double min_dist = numeric_limits<double>::max();
        for(int i = 0; i<(int) arcs.size(); ++i){
            int v1 = getArco(arcs[i])->getNodo1();
            int v2 = getArco(arcs[i])->getNodo2();
            int vv = v1;
            if(v1 == nn){
                vv = v2;
            }
            if(nodos_usados.find(vv) == nodos_usados.end()){
                double new_dist = getNodo(vv)->distancia(nodo2);
                if(new_dist < min_dist){
                    min_dist = new_dist;
                    nodo_elegido = vv;
                }
            }
        }
        if(min_dist > distancia_inicial){
            return false;

        }
    }
    return true;

}

/*** TRANSFORMACIONES: ***/
void Malla::moverNodosSegunConcentracion(double val) {
	nodos->moverTodosSegunConcentracion(val);
}

void Malla::moverNodosSegunParametro(int indice, double valor){

    int nNodos = getMaxIndiceNodos();
    double xs[nNodos +1];
    double ys[nNodos +1];
    double zs[nNodos +1];

    for(int i = 0; i <= nNodos; ++i){
        xs[i] = 0.0;
        ys[i] = 0.0;
        zs[i] = 0.0;
    }

    for(int i = 0; i < this->getNodos()->n_marcados; ++i){
        Punto *p = this->movimientos->getMovimiento(i, indice);
        int ind = this->getNodos()->nodos_marcados[i];
        xs[ind] = p->getX();
        ys[ind] = p->getY();
        zs[ind] = p->getZ();
    }

    for(int i = 0; i <= nNodos; ++i){
        Nodo *n = getNodo(i);
        int i1 = n->getAsociado1();
        int i2 = n->getAsociado2();
        int i3 = n->getAsociado3();

        if(i1<0 || i2<0 || i3<0)
            continue;

        float coef1 = n->getCoef1();
        float coef2 = n->getCoef2();
        float coef3 = n->getCoef3();

        float newX = n->getPunto().getX() + coef1*xs[i1]*valor + coef2*xs[i2]*valor + coef3*xs[i3]*valor;
        float newY = n->getPunto().getY() + coef1*ys[i1]*valor + coef2*ys[i2]*valor + coef3*ys[i3]*valor;
        float newZ = n->getPunto().getZ() + coef1*zs[i1]*valor + coef2*zs[i2]*valor + coef3*zs[i3]*valor;

        n->setPunto(Punto(newX, newY, newZ));
    }

}

Malla *Malla::nextMalla(){
    return sgteMalla;
}

void Malla::setNextMalla(Malla *m){
    sgteMalla = m;
}

void Malla::moverMallaModeloSegunAUV(int ind, double val){
    nodos->moverTodosAUV(ind, val);
}

void Malla::asignar_nodos_marcados(int *clos, int n){
    nodos->asignar_nodos_marcados(clos, n);
}

void Malla::moverNodosSegunShapeUnit(int ind, double val){
    nodos->moverShapeUnit(ind, val);
}

int Malla::checkMalla(bool imprimir){
	bool errores = false;
	//Chequeamos los nodos.
	for(int i=0; i<nodos->getNumNodos(); i++)
			if(nodos->getNodo(i)!=NULL)
				if(checkNodo(i,imprimir)==-1) {
					errores = true;
				}

	//Chequeamos los arcos.
	for(int i=0; i<arcos->getNumArcos(); i++)
			if(arcos->getArco(i)!=NULL)
				if(checkArco(i,imprimir)==-1) {
					errores = true;
				}

	//Chequeamos las caras.
	for(int i=0; i<caras->getNumCaras(); i++)
			if(caras->getCara(i)!=NULL)
				if(checkCara(i,imprimir)==-1) {
					errores = true;
				}
	if(errores) {
		if(imprimir)
			cout << "Hay errores en la malla." << endl << endl;
		return -1;
	}
	if(imprimir)
		cout << "La malla esta correcta." << endl << endl;
	return 0;
	}

/*
* Chequea la consistencia del nodo, esto es, que los arcos
* y caras a los que apunta apunten también a él
*/
int Malla::checkNodo(int indNodo,bool imprimir){
	Nodo* nodo=nodos->getNodo(indNodo);
	vector<int> indCaras=nodo->getCaras();
	vector<int> indArcos=nodo->getArcos();
	for (int i=0; i<(int)indCaras.size(); i++){
		Cara *c=caras->getCara(indCaras[i]);
		if (c==NULL){
			if(imprimir)
				cout << "Error en la Malla. Nodo " << indNodo << " apunta a Cara Vecina " << indCaras[i] << " la cual es nula." << endl;
			return -1;
			}
		else if(!c->perteneceNodo(indNodo)){
			if(imprimir)
				cout << "Error en la Malla. Nodo " << indNodo << " apunta a Cara Vecina " << indCaras[i] << " la cual no apunta al nodo." << endl;
			return -1;
			}
		}

	for (int i=0; i<(int)indArcos.size(); i++){
		Arco *a=arcos->getArco(indArcos[i]);
		if (a==NULL){
			if(imprimir)
				cout << "Error en la Malla. Nodo " << indNodo << " apunta a Arco Vecino " << indArcos[i] << " el cual es nulo." << endl;
			return -1;
			}
		else if(!a->perteneceNodo(indNodo)){
			if(imprimir)
				cout << "Error en la Malla. Nodo " << indNodo << " apunta a Arco Vecino " << indArcos[i] << " el cual no apunta al nodo." << endl;
			return -1;
			}
		}

	return 0;
	}

/*
* Chequea la consistencia del arco, esto es, que los nodos
* y caras a los que apunta apunten también a él
*/
int Malla::checkArco(int indArco,bool imprimir){
	Arco* arco=arcos->getArco(indArco);

	int ind_c1 = arco->getCara1(),
		ind_c2 = arco->getCara2(),
		ind_n1 = arco->getNodo1(),
		ind_n2 = arco->getNodo2();

	Cara *c1 = ind_c1!=-1 ? caras->getCara(ind_c1):NULL,
		*c2 = ind_c2!=-1 ? caras->getCara(ind_c2):NULL;
	Nodo *n1 = ind_n1!=-1 ? nodos->getNodo(ind_n1):NULL,
		*n2 = ind_n2!=-1 ? nodos->getNodo(ind_n2):NULL;

	// Verficar que existan las caras y nodos a los que apunta el arco
	if (ind_c1!=-1 && c1==NULL) {
		if(imprimir)
			cout << "Error en la Malla. Arco " << indArco << " apunta a Cara Vecina " << ind_c1 << " la cual es nula." << endl;
		return -1;
	}
	if (ind_c2!=-1 && c2==NULL){
		if(imprimir)
			cout << "Error en la Malla. Arco " << indArco << " apunta a Cara Vecina " << ind_c2 << " la cual es nula." << endl;
		return -1;
		}
	if (ind_n1!=-1 && n1==NULL){
		if(imprimir)
			cout << "Error en la Malla. Arco " << indArco << " apunta a Nodo Vecino " << ind_n1 << " el cual es nulo." << endl;
		return -1;
		}
	if (ind_n2!=-1 && n2==NULL){
		if(imprimir)
			cout << "Error en la Malla. Arco " << indArco << " apunta a Nodo Vecino " << ind_n2 << " el cual es nulo." << endl;
		return -1;
		}

	// Verificar que el arco apunte a caras y nodos que lo apuntan
	if(c1!=NULL && !c1->perteneceArco(indArco)) {
		if(imprimir)
			cout << "Error en la Malla. Arco " << indArco << " apunta a Cara Vecina " << ind_c1 << " la cual no apunta al arco." << endl;
		return -1;
		}
	if(c2!=NULL && !c2->perteneceArco(indArco)) {
		if(imprimir)
			cout << "Error en la Malla. Arco " << indArco << " apunta a Cara Vecina " << ind_c2 << " la cual no apunta al arco." << endl;
		return -1;
		}
	if(n1!=NULL && !n1->perteneceAArco(indArco)) {
		if(imprimir)
			cout << "Error en la Malla. Arco " << indArco << " apunta a Nodo Vecino " << ind_n1 << " el cual no apunta al arco." << endl;
		return -1;
		}
	if(n2!=NULL && !n2->perteneceAArco(indArco)) {
		if(imprimir)
			cout << "Error en la Malla. Arco " << indArco << " apunta a Nodo Vecino " << ind_n2 << " el cual no apunta al arco." << endl;
		return -1;
		}
	return 0;
	}

/*
* Chequea la consistencia de la cara, esto es, que los nodos
* y arcos a los que apunta apunten también a él.
* Además chequea que la cara esté compuesta de tres nodos y arcos distintos
*/
int Malla::checkCara(int indCara,bool imprimir){
	Cara* cara=caras->getCara(indCara);
	if (!cara->check(this)){
		if(imprimir)
			cout << "Error en la Malla. Cara " << indCara << " tiene nodos o arcos repetidos: " << cara << endl;
		return -1;
	}
	vector<int> indNodos=cara->getNodos();
	vector<int> indArcos=cara->getArcos();
	for (int i=0; i<(int)indNodos.size(); i++){
		Nodo* n=nodos->getNodo(indNodos[i]);
		if (n==NULL) {
			if(imprimir)
				cout << "Error en la Malla. Cara " << indCara << " apunta a Nodo Vecino " << indNodos[i] << " el cual es nulo." << endl;
			return -1;
		}
		else if(!n->perteneceACara(indCara)) {
			if(imprimir)
				cout << "Error en la Malla. Cara " << indCara << " apunta a Nodo Vecino " << indNodos[i] << " el cual no apunta a ella." << endl;
			return -1;
		}
	}
	for (int i=0; i<(int)indArcos.size(); i++){
		Arco *a=arcos->getArco(indArcos[i]);
		if (a==NULL) {
			if(imprimir)
				cout << "Error en la Malla. Cara " << indCara << " apunta a Arco Vecino " << indArcos[i] << " el cual es nulo." << endl;
			return -1;
		}
		if(!a->perteneceACara(indCara)) {
			if(imprimir)
				cout << "Error en la Malla. Cara " << indCara << " apunta a Arco Vecino " << indArcos[i] << " el cual no apunta a ella." << endl;
			return -1;
		}
		if(find(indNodos.begin(),indNodos.end(),a->getNodo1())==indNodos.end()) {
			if(imprimir)
				cout << "Error en la Malla. El nodo " << a->getNodo1() << " está en el Arco " << indArcos[i] << ", pero no en la cara." << endl;
			return -1;
		}
		if(find(indNodos.begin(),indNodos.end(),a->getNodo2())==indNodos.end()) {
			if(imprimir)
				cout << "Error en la Malla. El nodo " << a->getNodo2() << " está en el Arco " << indArcos[i] << ", pero no en la cara " << indCara << endl;
			return -1;
		}
	}

	return 0;
}

/*
* Chequea la consistencia de la cara, esto es, que los nodos
* y arcos a los que apunta apunten también a él.
* Además chequea que la cara esté compuesta de tres nodos y arcos distintos
*/
int Malla::checkCara_debil(int indCara,bool imprimir){
	Cara* cara=caras->getCara(indCara);
	if (!cara->check(this)){
		if(imprimir)
			cout << "Error en la Malla. Cara " << indCara << " tiene nodos o arcos repetidos: " << cara << endl;
		return -1;
	}
	vector<int> indNodos=cara->getNodos();
	vector<int> indArcos=cara->getArcos();
	for (int i=0; i<(int)indNodos.size(); i++){
		Nodo* n=nodos->getNodo(indNodos[i]);
		if (n==NULL) {
			if(imprimir)
				cout << "Error en la Malla. Cara " << indCara << " apunta a Nodo Vecino " << indNodos[i] << " el cual es nulo." << endl;
			return -1;
		}
		else if(!n->perteneceACara(indCara)) {
			if(imprimir)
				cout << "Error en la Malla. Cara " << indCara << " apunta a Nodo Vecino " << indNodos[i] << " el cual no apunta a ella." << endl;
			return -1;
		}
	}
	for (int i=0; i<(int)indArcos.size(); i++){
		Arco *a=arcos->getArco(indArcos[i]);
		if (a==NULL) {
			if(imprimir)
				cout << "Error en la Malla. Cara " << indCara << " apunta a Arco Vecino " << indArcos[i] << " el cual es nulo." << endl;
			return -1;
		}
		if(!a->perteneceACara(indCara)) {
			if(imprimir)
				cout << "Error en la Malla. Cara " << indCara << " apunta a Arco Vecino " << indArcos[i] << " el cual no apunta a ella." << endl;
			return -1;
		}
	}

	return 0;
}

string Malla::getTipoMalla() {
	string tipo = caras->getCara(0)->getEtiqueta();
	for(int i=1; i<caras->getNumCaras(); ++i) {
		Cara *c = caras->getCara(i);
		if(c != 0) {
			string tipo_cara = caras->getCara(i)->getEtiqueta();
			if(tipo_cara != tipo) {
				tipo = "mixed";
				break;
			}
		}
	}
	return tipo;
}

/*** OBTENCIÓN DE ÍNDICES: ***/
int Malla::getSiguienteCara(int indice, int ind_cara) {
	assert((indice < arcos->getNumArcos()) && (indice >= 0));
	assert((ind_cara < caras->getNumCaras()) && (ind_cara >= 0));

	int ind_c1 = arcos->getArco(indice)->getCara1();
	int ind_c2 = arcos->getArco(indice)->getCara2();

	if(ind_cara == ind_c1) {
		return ind_c2;
	}
	else if(ind_cara == ind_c2) {
		return ind_c1;
	}
	else {
		return -1;
	}
}

int Malla::getArcoOpuestoNodo(int ind_cara, int ind_nodo) {
	assert((ind_nodo < nodos->getNumNodos()) && (ind_nodo >= 0));
	assert((ind_cara < caras->getNumCaras()) && (ind_cara >= -1));

	if(ind_cara == -1) {
		return -1;
	}

	vector<int> ind_arcos = caras->getCara(ind_cara)->getArcos();
	for(int i=0; i<(int)ind_arcos.size(); i++) {
		int ind1 = arcos->getArco(ind_arcos[i])->getNodo1();
		int ind2 = arcos->getArco(ind_arcos[i])->getNodo2();
		if(ind_nodo != ind1 && ind_nodo != ind2) {
			return ind_arcos[i];
		}
	}
	return -1;
}

int Malla::getNodoOpuestoNodo(int ind_cara, int ind_nodo) {
	assert((ind_nodo < nodos->getNumNodos()) && (ind_nodo >= 0));
	assert((ind_cara < caras->getNumCaras()) && (ind_cara >= 0));

	int ind_arco = this->getArcoOpuestoNodo(ind_cara, ind_nodo);
	int ind_cara_vecina = this->getSiguienteCara(ind_arco,ind_cara);
	return this->getNodoOpuestoArco(ind_cara_vecina,ind_arco);
}

int Malla::getNodoOpuestoArco(int ind_cara, int ind_arco) {
	assert((ind_cara < caras->getNumCaras()) && (ind_cara >= -1));
	assert((ind_arco < arcos->getNumArcos()) && (ind_arco >= 0));

	if(ind_cara == -1) {
		return -1;
	}

	vector<int> ind_nodos = caras->getCara(ind_cara)->getNodos();
	vector<int> ind_arcos = caras->getCara(ind_cara)->getArcos();
	int ind1 = arcos->getArco(ind_arco)->getNodo1();
	int ind2 = arcos->getArco(ind_arco)->getNodo2();
	for(int i=0; i<(int)ind_nodos.size(); i++) {
		if(ind_nodos[i] != ind1 && ind_nodos[i] != ind2) {
			return ind_nodos[i];
		}
	}
	return -1;
}

int Malla::getCaraOpuestaNodo(int ind_cara, int ind_nodo) {
	assert((ind_nodo < nodos->getNumNodos()) && (ind_nodo >= 0));
	assert((ind_cara < caras->getNumCaras()) && (ind_cara >= -1));

	if(ind_cara == -1) {
		return -1;
	}

	int ind_arco = this->getArcoOpuestoNodo(ind_cara, ind_nodo);
	int ind_cara_vecina = this->getSiguienteCara(ind_arco,ind_cara);

	return ind_cara_vecina;
}

vector<int> Malla::getArcosNoIncidentes(int ind_cara, int ind_nodo) {
	assert((ind_nodo < nodos->getNumNodos()) && (ind_nodo >= 0));
	assert((ind_cara < caras->getNumCaras()) && (ind_cara >= -1));

	vector<int> ind_arcos;

	if(ind_cara == -1) {
		return ind_arcos;
	}

	vector<int> ind_arcos_cara = caras->getCara(ind_cara)->getArcos();
	for(int i=0; i<(int)ind_arcos_cara.size(); i++) {
		int ind1 = arcos->getArco(ind_arcos_cara[i])->getNodo1();
		int ind2 = arcos->getArco(ind_arcos_cara[i])->getNodo2();
		if(ind_nodo != ind1 && ind_nodo != ind2) {
			ind_arcos.push_back(ind_arcos_cara[i]);
		}
	}
	return ind_arcos;
}

vector<int> Malla::getCarasVecinasSinNodo(int ind_cara, int ind_nodo) {
	assert((ind_nodo < nodos->getNumNodos()) && (ind_nodo >= 0));
	assert((ind_cara < caras->getNumCaras()) && (ind_cara >= -1));

	vector<int> ind_caras_vecinas;

	if(ind_cara == -1) {
		return ind_caras_vecinas;
	}

	vector<int> ind_arcos = this->getArcosNoIncidentes(ind_cara, ind_nodo);
	for(int i=0; i<(int)ind_arcos.size(); ++i)
		ind_caras_vecinas.push_back(this->getSiguienteCara(ind_arcos[i],ind_cara));

	return ind_caras_vecinas;
}

int Malla::getArcoDiferente(int ind_cara, int ind_arco, int ind_nodo) {
	assert((ind_nodo < nodos->getNumNodos()) && (ind_nodo >= 0));
	assert((ind_cara < caras->getNumCaras()) && (ind_cara >= -1));
	assert((ind_arco < arcos->getNumArcos()) && (ind_arco >= 0));

	if(ind_cara == -1) {
		return -1;
	}

	vector<int> ind_arcos = caras->getCara(ind_cara)->getArcos();
	for(int i=0; i<(int)ind_arcos.size(); i++) {
		int ind1 = arcos->getArco(ind_arcos[i])->getNodo1();
		int ind2 = arcos->getArco(ind_arcos[i])->getNodo2();
		if((ind_nodo == ind1 || ind_nodo == ind2) && ind_arcos[i] != ind_arco) {
			return ind_arcos[i];
		}
	}
	assert(false);
	return -1;


}
/*** OTROS MÉTODOS: ***/
void Malla::setNormales() {

	for(int i=0; i<nodos->getNumNodos(); i++){
		if(nodos->getNodo(i) != 0) {
			vector<int> ind_caras = (nodos->getNodo(i))->getCaras();
			Vect normal;
			for (int j=0; j<(int)ind_caras.size(); j++){
				Cara *c = this->getCara(ind_caras[j]);
				Vect n = c->getNormal(this);
				normal = n*c->getAnguloVertice(i,this) + normal;
				}
			normal = normal*(1/normal.largo());
			nodos->getNodo(i)->setNormal(normal);
			}
		}
	}

Vect Malla::calcularNormalNodo(int ind_nodo) {
	assert((ind_nodo < nodos->getNumNodos()) && (ind_nodo >= 0) && nodos->getNodo(ind_nodo) != 0);
	vector<int> ind_caras = (nodos->getNodo(ind_nodo))->getCaras();
	Vect normal;
	for (int i=0; i<(int)ind_caras.size(); i++){
		Cara *c = this->getCara(ind_caras[i]);
		normal = c->getNormal(this)*c->getAnguloVertice(ind_nodo,this) + normal;
		}
	normal = normal * (1/normal.largo());
	return normal;
}

void Malla::setConcentracionTodos(double val) {
	for(int i=0; i<nodos->getNumNodos(); i++){
		if(nodos->getNodo(i) != 0) {
			nodos->getNodo(i)->setConcentracion(val);
		}
	}
}

Vect Malla::getNormalNodos(int ind_p1, int ind_p2, int ind_p3) {
	assert((ind_p1 < nodos->getNumNodos()) && (ind_p1 >= 0));
	assert((ind_p2 < nodos->getNumNodos()) && (ind_p2 >= 0));
	assert((ind_p3 < nodos->getNumNodos()) && (ind_p3 >= 0));
	Punto p1,p2,p3;
	p1 = nodos->getNodo(ind_p1)->getPunto();
	p2 = nodos->getNodo(ind_p2)->getPunto();
	p3 = nodos->getNodo(ind_p3)->getPunto();
	Vect vp1(p1);
	Vect vp2(p2);
	Vect vp3(p3);
	Vect v12 = vp2 - vp1;
	Vect v23 = vp3 - vp2;
	Vect N = v12.prodCruz(v23);
	return N;
}


/*** MÉTODOS DIRIGIDOS AL DESPLAZAMIENTO DE LA MALLA: ***/
vector<double> Malla::getValoresVolumenCero(int ind_arco) {
	assert((ind_arco < arcos->getNumArcos()) && (ind_arco >= 0));

	vector<double> raices;

	int ind_c1 = arcos->getArco(ind_arco)->getCara1();
	int ind_c2 = arcos->getArco(ind_arco)->getCara2();

	if(ind_c1 < 0 || ind_c2 < 0) {
		return raices; // este arco no define 2 caras --> region borde.
	}

	//sacamos los indices de los 4 puntos
	int ind_p1 = arcos->getArco(ind_arco)->getNodo1();
	int ind_p2 = arcos->getArco(ind_arco)->getNodo2();
	int ind_p_cara1 = this->getNodoOpuestoArco(ind_c1,ind_arco);
	int ind_p_cara2 = this->getNodoOpuestoArco(ind_c2,ind_arco);

	Punto p1 = nodos->getNodo(ind_p1)->getPunto();
	Punto p2 = nodos->getNodo(ind_p2)->getPunto();
	Punto p3 = nodos->getNodo(ind_p_cara1)->getPunto();
	Punto p4 = nodos->getNodo(ind_p_cara2)->getPunto();

	//Obtenemos los vectores normales a cada nodo y los multiplicamos por su concentración.
	Vect norm1 = nodos->getNodo(ind_p1)->getNormal();
	Vect normal1 = norm1 * nodos->getNodo(ind_p1)->getConcentracion();
	Vect norm2 = nodos->getNodo(ind_p2)->getNormal();
	Vect normal2 = norm2 * nodos->getNodo(ind_p2)->getConcentracion();
	Vect norm3 = nodos->getNodo(ind_p_cara1)->getNormal();
	Vect normal3 = norm3 * nodos->getNodo(ind_p_cara1)->getConcentracion();
	Vect norm4 = nodos->getNodo(ind_p_cara2)->getNormal();
	Vect normal4 = norm4 * nodos->getNodo(ind_p_cara2)->getConcentracion();

	Polinomio* aux1;
	Polinomio* aux2;

	vector<Polinomio*> pol1;
	pol1.push_back(new Polinomio(p1.getX(),normal1.getPunto().getX()));
	pol1.push_back(new Polinomio(p1.getY(),normal1.getPunto().getY()));
	pol1.push_back(new Polinomio(p1.getZ(),normal1.getPunto().getZ()));

	vector<Polinomio*> pol2;
	pol2.push_back(new Polinomio(p2.getX(),normal2.getPunto().getX()));
	pol2.push_back(new Polinomio(p2.getY(),normal2.getPunto().getY()));
	pol2.push_back(new Polinomio(p2.getZ(),normal2.getPunto().getZ()));

	vector<Polinomio*> pol3;
	pol3.push_back(new Polinomio(p3.getX(),normal3.getPunto().getX()));
	pol3.push_back(new Polinomio(p3.getY(),normal3.getPunto().getY()));
	pol3.push_back(new Polinomio(p3.getZ(),normal3.getPunto().getZ()));

	vector<Polinomio*> pol4;
	pol4.push_back(new Polinomio(p4.getX(),normal4.getPunto().getX()));
	pol4.push_back(new Polinomio(p4.getY(),normal4.getPunto().getY()));
	pol4.push_back(new Polinomio(p4.getZ(),normal4.getPunto().getZ()));

	vector<Polinomio*> pol_a;
	pol_a.push_back((*pol2[0])-pol1[0]);
	pol_a.push_back((*pol2[1])-pol1[1]);
	pol_a.push_back((*pol2[2])-pol1[2]);

	vector<Polinomio*> pol_b;
	pol_b.push_back((*pol3[0])-pol1[0]);
	pol_b.push_back((*pol3[1])-pol1[1]);
	pol_b.push_back((*pol3[2])-pol1[2]);

	vector<Polinomio*> pol_c;
	pol_c.push_back((*pol4[0])-pol1[0]);
	pol_c.push_back((*pol4[1])-pol1[1]);
	pol_c.push_back((*pol4[2])-pol1[2]);

	vector<Polinomio*> pol_b_cruz_c;
	aux1=(*pol_b[1])*pol_c[2];
	aux2=(*pol_b[2])*pol_c[1];
	pol_b_cruz_c.push_back((*aux1)-aux2);
	delete aux1; delete aux2;
	aux1=(*pol_b[2])*pol_c[0];
	aux2=(*pol_b[0])*pol_c[2];
	pol_b_cruz_c.push_back((*aux1)-aux2);
	delete aux1; delete aux2;
	aux1=(*pol_b[0])*pol_c[1];
	aux2=(*pol_b[1])*pol_c[0];
	pol_b_cruz_c.push_back((*aux1)-aux2);
	delete aux1; delete aux2;

	vector<Polinomio*> pol_abc;
	pol_abc.push_back((*pol_a[0])*pol_b_cruz_c[0]);
	pol_abc.push_back((*pol_a[1])*pol_b_cruz_c[1]);
	pol_abc.push_back((*pol_a[2])*pol_b_cruz_c[2]);

	aux1=(*pol_abc[1])+pol_abc[2];
	Polinomio *final = (*pol_abc[0]) + aux1;
	delete aux1;

	int n;
	double x1, x2, x3;

	if((*final)[3] != 0) {
		n = final->getRaicesCubicas(x1,x2,x3);
		raices.push_back(x1);
		if(n == 3) {
			raices.push_back(x1);
			raices.push_back(x2);
			raices.push_back(x3);
		}
	}
	else if((*final)[2] != 0) {
		n = final->getRaicesCuadradas(x1,x2);
		if(n == 2) {
			raices.push_back(x1);
			raices.push_back(x2);
		}
	}
	else if((*final)[1] != 0){
		n = final->getRaizLineal(x1);
		raices.push_back(x1);
	}
	else {
		n = 0;
	}

	//Libero memoria de los polinomios usados.
	for (int i=0; i<(int)pol1.size() ; i++)
		delete pol1[i];
	for (int i=0; i<(int)pol2.size() ; i++)
		delete pol2[i];
	for (int i=0; i<(int)pol3.size() ; i++)
		delete pol3[i];
	for (int i=0; i<(int)pol4.size() ; i++)
		delete pol4[i];
	for (int i=0; i<(int)pol_a.size() ; i++)
		delete pol_a[i];
	for (int i=0; i<(int)pol_b.size() ; i++)
		delete pol_b[i];
	for (int i=0; i<(int)pol_c.size() ; i++)
		delete pol_c[i];
	for (int i=0; i<(int)pol_b_cruz_c.size() ; i++)
		delete pol_b_cruz_c[i];
	for (int i=0; i<(int)pol_abc.size() ; i++)
		delete pol_abc[i];
	delete final;

	return raices;
}

int Malla::getTipoMovRegion(int ind_arco, double val) {
	assert((ind_arco < arcos->getNumArcos()) && (ind_arco >= 0));

	int ind_c1 = arcos->getArco(ind_arco)->getCara1();
	int ind_c2 = arcos->getArco(ind_arco)->getCara2();

	if(ind_c1 < 0 || ind_c2 < 0) {
		return -1; // region borde
	}

	//obtenemos los indices de los 4 puntos
	int ind_p1 = arcos->getArco(ind_arco)->getNodo1();
	int ind_p2 = arcos->getArco(ind_arco)->getNodo2();
	int ind_p_c1 = this->getNodoOpuestoArco(ind_c1,ind_arco);
	int ind_p_c2 = this->getNodoOpuestoArco(ind_c2,ind_arco);

	//movemos los 4 nodos.
	nodos->moverNodoSegunConcentracion(ind_p1,val);
	nodos->moverNodoSegunConcentracion(ind_p2,val);
	nodos->moverNodoSegunConcentracion(ind_p_c1,val);
	nodos->moverNodoSegunConcentracion(ind_p_c2,val);

	int tipo_region = this->tipArco(ind_arco);

	//regresamos los 4 nodos.
	nodos->regresarNodoSegunConcentracion(ind_p1,val);
	nodos->regresarNodoSegunConcentracion(ind_p2,val);
	nodos->regresarNodoSegunConcentracion(ind_p_c1,val);
	nodos->regresarNodoSegunConcentracion(ind_p_c2,val);

	return tipo_region;
}

int Malla::tipArco(int ind_arco) {
	assert((ind_arco < arcos->getNumArcos()) && (ind_arco >= 0));

	int ind_c1 = arcos->getArco(ind_arco)->getCara1();
	int ind_c2 = arcos->getArco(ind_arco)->getCara2();

	if(ind_c1 < 0 || ind_c2 < 0) {
		return NO_TIP; // region borde ==> no hay tip
	}

	//obtenemos los indices de los 4 puntos
	int ind_p1 = arcos->getArco(ind_arco)->getNodo1();
	int ind_p2 = arcos->getArco(ind_arco)->getNodo2();
	int ind_p_c1 = this->getNodoOpuestoArco(ind_c1,ind_arco);
	int ind_p_c2 = this->getNodoOpuestoArco(ind_c2,ind_arco);

	Punto p1 = nodos->getNodo(ind_p1)->getPunto();
	Punto p2 = nodos->getNodo(ind_p2)->getPunto();
	Punto p_c1 = nodos->getNodo(ind_p_c1)->getPunto();
	Punto p_c2 = nodos->getNodo(ind_p_c2)->getPunto();

	int tip_p_c1 = this->puntoInCara(p_c1,ind_c2);
	int tip_p_c2 = this->puntoInCara(p_c2,ind_c1);

	if(tip_p_c1 == TIP_ON_VERTEX || tip_p_c2 == TIP_ON_VERTEX) {
		return TIP_ON_VERTEX;
	}
	else if(tip_p_c1 == TIP_ON_EDGE || tip_p_c2 == TIP_ON_EDGE) {
		return TIP_ON_EDGE;
	}
	else if(tip_p_c1 == TIP_INSIDE || tip_p_c2 == TIP_INSIDE) {
		return TIP_INSIDE;
	}
	else {
		if(seCruzan(p1,p_c2,p2,p_c1) == 1 || seCruzan(p1,p_c1,p2,p_c2) == 1) {
			return TIP_OUTSIDE_A;
		}
		else {
			return TIP_OUTSIDE_B;
		}
	}
}

int Malla::puntoInCara(Punto p, int ind_cara) {
	assert((ind_cara < caras->getNumCaras()) && (ind_cara >= -1));
	if(ind_cara == -1) {
		return NO_TIP;
	}

	Cara *c = caras->getCara(ind_cara);
	Vect normal_cara = c->getNormal(this);
	vector<int> ind_puntos = c->getNodos();
	Punto p0 = nodos->getNodo(ind_puntos[0])->getPunto();
	Punto p1 = nodos->getNodo(ind_puntos[1])->getPunto();
	Punto p2 = nodos->getNodo(ind_puntos[2])->getPunto();
	Vect vp(p.getX(),p.getY(),p.getZ());
	Vect vp0(p0);
	Vect vp1(p1);
	Vect vp2(p2);
	Vect v_p0_p = vp - vp0;

	double prod = normal_cara.prodPunto(v_p0_p);

	// verificamos que el punto este en el plano
	//(prod == 0); --> seria la condicion con aritmetica exacta.
	if(prod >= 0.0000000000001 || prod <= -0.0000000000001) {
		return NO_TIP_YET;
	}

	Vect v_p0_p1 = vp1 - vp0;
	Vect v_p1_p2 = vp2 - vp1;
	Vect v_p2_p0 = vp0 - vp2;

	Vect v_p1_p = vp - vp1;
	Vect v_p2_p = vp - vp2;

	if(v_p0_p.largo() == 0 || v_p1_p.largo() == 0 || v_p2_p.largo() == 0) {
		return TIP_ON_VERTEX;
	}

	Vect v0 = v_p0_p1.prodCruz(v_p0_p);
	Vect v1 = v_p1_p2.prodCruz(v_p1_p);
	Vect v2 = v_p2_p0.prodCruz(v_p2_p);

	if(v0.largo() == 0 && v_p1_p.largo() < v_p0_p1.largo() && v_p0_p.largo() < v_p0_p1.largo()) {
		return TIP_ON_EDGE;
	}
	if(v1.largo() == 0 && v_p2_p.largo() < v_p1_p2.largo() && v_p1_p.largo() < v_p1_p2.largo()) {
		return TIP_ON_EDGE;
	}
	if(v2.largo() == 0 && v_p0_p.largo() < v_p2_p0.largo() && v_p2_p.largo() < v_p2_p0.largo()) {
		return TIP_ON_EDGE;
	}

	if(normal_cara.largo() == 0) {
		return TIP_OUTSIDE;
	}

	double prod_punto1 = normal_cara.prodPunto(v0);
	double prod_punto2 = normal_cara.prodPunto(v1);
	double prod_punto3 = normal_cara.prodPunto(v2);

	if(prod_punto1 < 0 || prod_punto2 < 0 || prod_punto3 < 0) {
		return TIP_OUTSIDE; // esta fuera de la cara
	}
	else {
		return TIP_INSIDE; // esta dentro de la cara
	}
}

int Malla::seCruzan(Punto p1_arco1, Punto p2_arco1, Punto p1_arco2, Punto p2_arco2) {

	Vect vp1_arco1(p1_arco1);
	Vect vp2_arco1(p2_arco1);
	Vect vp1_arco2(p1_arco2);
	Vect vp2_arco2(p2_arco2);

	Vect v_arco1 = vp2_arco1 - vp1_arco1;
	Vect v_arco2 = vp2_arco2 - vp1_arco2;

	Vect v11 = v_arco1.prodCruz(vp1_arco2-vp1_arco1);
	Vect v12 = v_arco1.prodCruz(vp2_arco2-vp1_arco1);

	Vect v21 = v_arco2.prodCruz(vp1_arco1-vp1_arco2);
	Vect v22 = v_arco2.prodCruz(vp2_arco1-vp1_arco2);

	double prod1 = v11.prodPunto(v12);
	double prod2 = v21.prodPunto(v22);

	if(prod1 < 0 && prod2 < 0) {
		return 1; // si se cruzan
	}
	else {
		return 0; // no se cruzan
	}
}

double Malla::valorInterseccion(Punto p1_arco1, Punto p2_arco1, Punto p1_arco2, Punto p2_arco2) {
	Vect vp1_arco1(p1_arco1);
	Vect vp2_arco1(p2_arco1);
	Vect vp1_arco2(p1_arco2);
	Vect vp2_arco2(p2_arco2);

	Vect v_arco1 = vp2_arco1 - vp1_arco1;
	Vect v_arco2 = vp2_arco2 - vp1_arco2;

	Vect v_p1_arco12 = vp1_arco2-vp1_arco1;

	Vect normal_a1_a2 = v_arco1.prodCruz(v_arco2);

	double num = v_p1_arco12.prodPunto(v_arco2.prodCruz(normal_a1_a2));
	double den = normal_a1_a2.largo()*normal_a1_a2.largo();

	if(den == 0) {
		//los segmento son paralelos
		return -1;
	}
	else {
		return num/den;
	}
}

void Malla::recalcularMedula(){
	AdapterComputationalGeometry adapter;

	//Obtengo el y mas bajo del arbol.
	double ymin=numeric_limits<double>::max();
	for (int i=0; i<nodos->getNumNodos(); i++){
		Nodo* nodoActual=nodos->getNodo(i);
		if(nodoActual!=NULL && nodoActual->getPunto().getY()<ymin)
			ymin=nodoActual->getPunto().getY();
		}

	//Obtengo el y mas alto del arbol.
	double ymax=-1*numeric_limits<double>::max();
	for (int i=0; i<nodos->getNumNodos(); i++){
		Nodo* nodoActual=nodos->getNodo(i);
		if(nodoActual!=NULL && nodoActual->getPunto().getY()>ymax)
			ymax=nodoActual->getPunto().getY();
		}


	double yplano=ymin;
	int nsteps=100;
	double ystep=(ymax-ymin)/nsteps;

	//Calculamos intersecciones entre arcos y el plano en xz.
	Vect plano[3];
	Vect q,r;
	vector<Punto> intersecciones;
	vector<Punto> medula;
	double sumax,sumay, sumaz;
	char resultadointerseccion;
	for (int iplano=0; iplano<nsteps; iplano++){
		plano[0]=Vect(0,yplano,0);
		plano[1]=Vect(0,yplano,1);
		plano[2]=Vect(1,yplano,0);
		for (int i=0;i<arcos->getNumArcos(); i++){
			Arco* arcoActual=arcos->getArco(i);
			if (arcoActual!=NULL){
				q=Vect(nodos->getNodo(arcoActual->getNodo1())->getPunto());
				r=Vect(nodos->getNodo(arcoActual->getNodo2())->getPunto());
				resultadointerseccion=adapter.SegPlaneInt(plano, q, r);
				if (resultadointerseccion!='0'){
					intersecciones.push_back(arcos->getArco(i)->getPuntoMedio(this));

					}
				}
			}

		//Calculo el promedio de las intersecciones en el plano.
		sumax=0;
		sumay=0;
		sumaz=0;
		for (int j=0; j<(int)intersecciones.size(); j++){
			sumax=sumax+intersecciones[j].getX();
			sumay=sumay+intersecciones[j].getY();
			sumaz=sumaz+intersecciones[j].getZ();
			}

		medula.push_back(Punto(sumax/intersecciones.size(),yplano,sumaz/intersecciones.size()));

		yplano=yplano+ystep;
		intersecciones.clear();
		}

	setMedula(medula);
	}

void Malla::printfile() {
	//Lineas necesarias para que scanf lea archivo en computadores seteados en otro lenguaje.
	setlocale(LC_NUMERIC, "POSIX");

	FILE *archivo_x = fopen("/home/cristi/Desktop/debug.txt","w");

	fprintf(archivo_x,"NODOS: \n");
	for(int i = 0; i < nodos->getNumNodos(); ++i) {
		fprintf(archivo_x,"%d ",i);
		if(nodos->getNodo(i) != NULL)
			fprintf(archivo_x,"%s", nodos->getNodo(i)->imprimir().c_str());
		else
			fprintf(archivo_x,"NULL\n");
	}
	fprintf(archivo_x,"ARCOS: \n");
	for(int i = 0; i < arcos->getNumArcos(); ++i) {
		fprintf(archivo_x,"%d ",i);
		if(arcos->getArco(i) != NULL)
			fprintf(archivo_x,"%s",arcos->getArco(i)->imprimir().c_str());
		else
			fprintf(archivo_x,"NULL\n");
	}
	fprintf(archivo_x,"CARAS: \n");
	for(int i = 0; i < caras->getNumCaras(); ++i) {
		fprintf(archivo_x,"%d ",i);
		if(caras->getCara(i) != NULL)
			fprintf(archivo_x,"%s",caras->getCara(i)->imprimir().c_str());
		else
			fprintf(archivo_x,"NULL\n");
	}
    fclose(archivo_x);

	setlocale(LC_NUMERIC, "");

}

void Malla::print() {
	cout << "NODOS: " << endl;
	for(int i = 0; i < nodos->getNumNodos(); ++i) {
		cout << i << " ";
		if(nodos->getNodo(i) != NULL)
			nodos->getNodo(i)->imprimir();
		else
			cout << "NULL" << endl;
	}
	cout << "ARCOS: " << endl;
	for(int i = 0; i < arcos->getNumArcos(); ++i) {
		cout << i << " ";
		if(arcos->getArco(i) != NULL)
			arcos->getArco(i)->imprimir();
		else
			cout << "NULL" << endl;
	}
	cout << "CARAS: " << endl;
	for(int i = 0; i < caras->getNumCaras(); ++i) {
		cout << i << " ";
		if(caras->getCara(i) != NULL)
			caras->getCara(i)->imprimir();
		else
			cout << "NULL" << endl;
	}
}

Malla::~Malla(){
    if(sgteMalla != NULL){
        delete sgteMalla;
    }

	delete nodos;
	delete arcos;
	delete caras;
	delete fabrica_algoritmos;
}
