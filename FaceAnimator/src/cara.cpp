#include "cara.h"
#include <math.h>

Cara::Cara() {}

Cara::Cara(int n1, int n2, int n3, int a1, int a2, int a3) {
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

Cara::Cara(int n1, int n2, int n3) {
    num_elem = 3;
    ind_nodos.push_back(n1);
    ind_nodos.push_back(n2);
    ind_nodos.push_back(n3);
    rgb[0] = -1;
    rgb[1] = -1;
    rgb[2] = -1;
}

Cara::Cara(vector<int> ind_nds, vector<int> ind_arcs) {
    assert(ind_nds.size() == ind_arcs.size());
    num_elem = ind_nds.size();
    ind_nodos = ind_nds;
    ind_arcos = ind_arcs;
    rgb[0] = -1;
    rgb[1] = -1;
    rgb[2] = -1;
}

Cara *Cara::clone() {
	Cara *nueva_cara = new Cara(ind_nodos, ind_arcos);
	nueva_cara->setColores(rgb[0],rgb[1],rgb[2]);
	return nueva_cara;
}

void Cara::setNodos(vector<int> nds) {
    ind_nodos = nds;
}

void Cara::addNodo(int nodo) {
    for(int i=0; i<(int)ind_nodos.size(); i++) {
        if(ind_nodos[i] == nodo) {
            return;
        }
    }
    ind_nodos.push_back(nodo);
}

void Cara::eraseNodo(int nodo) {
    vector<int>::iterator iter;
    for(iter=ind_nodos.begin(); iter!=ind_nodos.end(); iter++) {
        if(*iter == nodo) {
            iter = ind_nodos.erase(iter);
            return;
        }
    }
}

void Cara::changeNodo(int nodo_sale, int nodo_entra) {
    for(int i=0; i<(int)ind_nodos.size(); i++) {
        if(ind_nodos[i] == nodo_sale) {
            ind_nodos[i] = nodo_entra;
            return;
        }
    }
}

vector<int> Cara::changeNodoCascada(int nodo_sale, int nodo_entra, Arcos *arcos) {
    bool cambio = false;
    vector<int> arcos_cambiados;
    for(int i=0; i<(int)ind_nodos.size(); i++) {
        if(ind_nodos[i] == nodo_sale) {
            ind_nodos[i] = nodo_entra;
            cambio = true;
            break;
        }
    }
    if(cambio) {
        for(int i=0; i<(int)ind_arcos.size(); i++) {
            cambio = arcos->getArco(ind_arcos[i])->changeNodo(nodo_sale, nodo_entra);
            if(cambio) {
				arcos_cambiados.push_back(ind_arcos[i]);
            }
       	}
    }
    return arcos_cambiados;
}

void Cara::changeArco(int arco_sale, int arco_entra){
	for(int i=0; i<(int)ind_arcos.size(); i++) {
        if(ind_arcos[i] == arco_sale) {
            ind_arcos[i] = arco_entra;
            return;
        	}
    	}
	}

vector<int> Cara::getNodos() {
    return ind_nodos;
}

void Cara::setArcos(vector<int> ars) {
    ind_arcos = ars;
}

void Cara::addArco(int arco) {
    for(int i=0; i<(int)ind_arcos.size(); i++) {
        if(ind_arcos[i] == arco) {
            return;
        }
    }
    ind_arcos.push_back(arco);
}

#include <algorithm>
void Cara::eraseArco(int arco) {
    vector<int>::iterator iter;
    for(iter=ind_arcos.begin(); iter!=ind_arcos.end(); iter++) {
        if(*iter == arco) {
            iter = ind_arcos.erase(iter);
            return;
        }
    }

}

vector<int> Cara::getArcos() {
    return ind_arcos;
}

int Cara::getPuntoDistinto(int p1, int p2) {
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

vector<int> Cara::getPuntosDistintos(int p1) {
	vector<int> puntosDistintos;
    int indice = -1;
    for(int i = 0; i < num_elem; ++i)
        if(ind_nodos[i] == p1) {
            indice = i;
            break;
        }
    for(int i = 1; i < num_elem; ++i)
        puntosDistintos.push_back(ind_nodos[(int)fmod(i+indice,num_elem)]);

	return puntosDistintos;
}

vector<int> Cara::getArcosNoIncidentes(int ind_nodo, Malla *malla) {
	vector<int> arcosNoIncidentes;
    for(int i = 0; i < num_elem; ++i) {
        Arco *arco = malla->getArco(ind_arcos[i]);
        if(!arco->perteneceNodo(ind_nodo))
            arcosNoIncidentes.push_back(ind_arcos[i]);
    }
	return arcosNoIncidentes;
}

vector<int> Cara::getArcosIncidentes(int ind_nodo, Malla *malla) {
	vector<int> arcosIncidentes;
    for(int i = 0; i < num_elem; ++i) {
        Arco *arco = malla->getArco(ind_arcos[i]);
        if(arco->perteneceNodo(ind_nodo))
            arcosIncidentes.push_back(ind_arcos[i]);
    }
	return arcosIncidentes;
}

int Cara::getNumElem() {
    return num_elem;
}

void Cara::setColores(float r, float g, float b) {
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
}

float Cara::getR() {
    return rgb[0];
}

float Cara::getG() {
    return rgb[1];
}

float Cara::getB() {
    return rgb[2];
}

bool Cara::perteneceArco(int ind_arco) {
    for(int i = 0; i < (int)ind_arcos.size(); ++i)
        if(ind_arcos[i] == ind_arco)
            return true;
    return false;
}

bool Cara::perteneceNodo(int ind_nodo) {
    for(int i = 0; i < (int)ind_nodos.size(); ++i)
        if(ind_nodos[i] == ind_nodo)
            return true;
    return false;
}

string Cara::getEtiqueta() {
	return "Cara";
}

/***/
double Cara::getArea(Malla *malla) {
	assert(malla != 0);

	Vect vp0 = Vect(malla->getNodo(ind_nodos[0])->getPunto());
	Vect vp1, vp2;
	Vect v1, v2, prod_cruz;
	double area = 0;
	for(int i=1; i<(int)ind_nodos.size()-1; i++) {
		vp1 = Vect(malla->getNodo(ind_nodos[i])->getPunto());
		vp2 = Vect(malla->getNodo(ind_nodos[i+1])->getPunto());
		v1 = vp1 - vp0;
		v2 = vp2 - vp0;
		prod_cruz = v1.prodCruz(v2);
		area = area + prod_cruz.largo()/2;
	}
	return area;
}

double Cara::getPerimetro(Malla *malla){
	assert(malla != 0);
	double perimetro=0;
	for (int i=0; i<num_elem; i++)
		perimetro+=malla->getArco(ind_arcos[i])->getLargo(malla);

	return perimetro;
}

double Cara::getAnguloVertice(int ind_nodo, Malla *malla) {
	assert(malla != 0 && ind_nodo >= 0 && ind_nodo <= malla->getMaxIndiceNodos());
	Punto p1, p2, p3;
	Vect v1, v2;
	double angulo;
	for(int i=0; i<(int)ind_nodos.size(); i++) {
		// Buscamos que el nodo ind_nodo esté al medio
		if(ind_nodo != ind_nodos[int(fmod(i+1,ind_nodos.size()))])
			continue;
		p1 = malla->getNodo(ind_nodos[i])->getPunto();
		p2 = malla->getNodo(ind_nodos[int(fmod(i+1,num_elem))])->getPunto();
		p3 = malla->getNodo(ind_nodos[int(fmod(i+2,num_elem))])->getPunto();
		Vect vp1(p1);
		Vect vp2(p2);
		Vect vp3(p3);
		v1 = vp1 - vp2;
		v2 = vp3 - vp2;
		angulo = v1.getAngulo(v2);
		return angulo;
	}
	// el indice del nodo no pertenece a la cara
	assert(false);
	return 0;
}

double Cara::getAnguloMin(Malla *malla) {
	assert(malla != 0);
	Vect normal_cara = this->getNormal(malla);
	Punto p1, p2, p3;
	Vect v1, v2, prod_cruz;
	double angulo;
	double angulo_min = 2*PI;
	for(int i=0; i<num_elem; i++) {
		p1 = malla->getNodo(ind_nodos[i])->getPunto();
		p2 = malla->getNodo(ind_nodos[int(fmod(i+1,num_elem))])->getPunto();
		p3 = malla->getNodo(ind_nodos[int(fmod(i+2,num_elem))])->getPunto();
		Vect vp1(p1);
		Vect vp2(p2);
		Vect vp3(p3);
		v1 = vp1 - vp2;
		v2 = vp3 - vp2;
		prod_cruz = v1.prodCruz(v2);
		angulo = v1.getAngulo(v2);
		if(normal_cara.prodPunto(prod_cruz) > 0) {
			angulo = 2*PI - angulo;
		}
		if(angulo < angulo_min) {
			angulo_min = angulo;
		}
	}

	return angulo_min;
}

double Cara::getAnguloMax(Malla *malla) {
	assert(malla != 0);
	//obtenemos los indices de los arcos de la cara
	Vect normal_cara = this->getNormal(malla);
	Punto p1, p2, p3;
	Vect v1, v2, prod_cruz;
	double angulo;
	double angulo_max = 0;
	for(int i=0; i<num_elem; i++) {
		p1 = malla->getNodo(ind_nodos[i])->getPunto();
		p2 = malla->getNodo(ind_nodos[int(fmod(i+1,num_elem))])->getPunto();
		p3 = malla->getNodo(ind_nodos[int(fmod(i+2,num_elem))])->getPunto();
		Vect vp1(p1);
		Vect vp2(p2);
		Vect vp3(p3);
		v1 = vp1 - vp2;
		v2 = vp3 - vp2;
		prod_cruz = v1.prodCruz(v2);
		angulo = v1.getAngulo(v2);
		if(normal_cara.prodPunto(prod_cruz) > 0) {
			angulo = 2*PI - angulo;
		}
		if(angulo > angulo_max) {
			angulo_max = angulo;
		}
	}
	return angulo_max;
}

vector<int> Cara::getArcosAnguloMin(Malla *malla) {
	assert(malla != 0);

	int ind_nodo_min = this->getNodoAnguloMin(malla);

	vector<int> arcos_angulo_min;
	vector<int> arcos_nodo = malla->getNodo(ind_nodo_min)->getArcos();

	for(int i=0; i<(int)arcos_nodo.size(); i++) {
		for(int j=0; j<num_elem; j++) {
			if(arcos_nodo[i] == ind_arcos[j]) {
				arcos_angulo_min.push_back(arcos_nodo[i]);
			}
		}
	}
	assert(arcos_angulo_min.size() == 2);
	return arcos_angulo_min;
}

int Cara::getNodoAnguloMin(Malla *malla) {
	assert(malla != 0);
	double angulo;
	int ind_nodo_min = -1;
	double angulo_min = 2*PI;
	for(int i=0; i<num_elem; i++) {
		angulo = this->getAnguloVertice(ind_nodos[i],malla);
		if(angulo < angulo_min) {
			angulo_min = angulo;
			ind_nodo_min = ind_nodos[i];
		}
	}
	return ind_nodo_min;
}

int Cara::getNodoAnguloMax(Malla *malla) {
	assert(malla != 0);
	double angulo;
	int ind_nodo_max = -1;
	double angulo_max = 0;
	for(int i=0; i<num_elem; i++) {
		angulo = this->getAnguloVertice(ind_nodos[i],malla);
		if(angulo > angulo_max) {
			angulo_max = angulo;
			ind_nodo_max = ind_nodos[i];
		}
	}
	return ind_nodo_max;
}

Vect Cara::getNormal(Malla *malla) {
	assert(malla != 0);
	Punto p1,p2,p3;
	p1 = malla->getNodo(ind_nodos[0])->getPunto();
	p2 = malla->getNodo(ind_nodos[1])->getPunto();
	p3 = malla->getNodo(ind_nodos[2])->getPunto();
	Vect vp1(p1);
	Vect vp2(p2);
	Vect vp3(p3);
	Vect v12 = vp2 - vp1;
	Vect v13 = vp3 - vp2;
	Vect N = v12.prodCruz(v13);
	N.normalizar();

	return N;
}

int Cara::getArcoMasLargo(Malla *malla) {
	assert(malla != 0);
	int ind_arco_mas_largo = ind_arcos[0];
	for(int i=1; i<num_elem; i++) {
		if(malla->getArco(ind_arcos[i])->getLargo(malla) > malla->getArco(ind_arco_mas_largo)->getLargo(malla)) {
			ind_arco_mas_largo = ind_arcos[i];
		}
	}
	return ind_arco_mas_largo;
}

int Cara::getArcoMasCorto(Malla *malla) {
	assert(malla != 0);
	int ind_arco_mas_corto = ind_arcos[0];
	for(int i=1; i<num_elem; i++) {
		if(malla->getArco(ind_arcos[i])->getLargo(malla) < malla->getArco(ind_arco_mas_corto)->getLargo(malla)) {
			ind_arco_mas_corto = ind_arcos[i];
		}
	}
	return ind_arco_mas_corto;
}

Cara *Cara::colapsarArco(Malla *malla,int ind_arco, int ind_nodo) {
    return this;
}


void Cara::ordenar(Malla *malla) {
	vector<int> nuevo_orden;
	for(int i = 0; i < num_elem; ++i) {
		int n1 = ind_nodos[i];
		int n2 = ind_nodos[int(fmod(i+1,num_elem))];
		for(int j = i, k = 0; k < num_elem; k++) { // recorro de esta forma para que el mejor caso sea cuando está ordenado
			int ind_arco = int(fmod(j++,num_elem));
			Arco *arco = malla->getArco(ind_arcos[ind_arco]);
			if(arco->perteneceNodo(n1) && arco->perteneceNodo(n2)) {
				nuevo_orden.push_back(ind_arcos[ind_arco]);
				break;
			}
		}
	}
	ind_arcos = nuevo_orden;
}

bool Cara::check(Malla *malla) {
	set<int> nodos_sin_repeticion;
	set<int> arcos_sin_repeticion;
	for(int i = 0; i < num_elem; ++i) {
		nodos_sin_repeticion.insert(ind_nodos[i]);
		arcos_sin_repeticion.insert(ind_arcos[i]);
	}
	if((int)nodos_sin_repeticion.size() != num_elem || (int)arcos_sin_repeticion.size() != num_elem)
        return false;
	for(int i = 0; i < num_elem; ++i) {
        if(this->getAnguloVertice(ind_nodos[i],malla) == 0) { //Cara degenerada, 3 nodos colineales
            cout << "Cara degenerada" << endl;
            return false;
        }
	}
	return true;
}

string Cara::imprimir() {
	string aux;
    ostringstream myStream;
    myStream << "Nodos: ";
    for(int i = 0; i < num_elem; ++i)
        myStream << ind_nodos[i] << " ";
    myStream << "   Arcos: ";
    for(int i = 0; i < (int)ind_arcos.size(); ++i)
        myStream << ind_arcos[i] << " ";
    myStream << endl;
    aux = myStream.str();
    cout << aux;
    return aux;
}

ostream& operator<<(ostream &os, Cara *c) {
    os << "Nodos: ";
    for(int i = 0; i < c->num_elem; ++i)
        os << c->ind_nodos[i] << " ";
    os << "   Arcos: ";
    for(int i = 0; i < (int)c->ind_arcos.size(); ++i)
        os << c->ind_arcos[i] << " ";
    return os;
}
