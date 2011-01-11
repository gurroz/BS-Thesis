#include "generacilindro.h"

GeneraCilindro::GeneraCilindro(double altura, double radio, int num_anillos, int num_puntos, int tipo):AlgGeneracion() {
    this->altura = altura;
    this->radio = radio;
    this->num_anillos = num_anillos;
    this->num_puntos = num_puntos;
    this->tipo = tipo;
}

Malla* GeneraCilindro::aplicar() {
    if(this->tipo == 0) {
        return this->generaMallaTriangulos();
    }
    else {
        return this->generaMallaCuadrilateros();
    }
}

Malla* GeneraCilindro::generaMallaTriangulos() {

    //Genero la medula.
    vector<Punto> medula;
    medula.push_back(Punto(0,0,0));
    medula.push_back(Punto(0,altura,0));

    nodos = new Nodos();
    Nodo *nodo;
    Punto p;
    Vect v, v1, v2;

    double h,angulo;
    h = altura / num_anillos;
    angulo = 2*PI / num_puntos;
    for(int i=0; i<num_anillos; i++) {
        for(int j=0; j<num_puntos; j++) {
            p = Punto(cos(j*angulo)*radio,i*h-h/2,sin(j*angulo)*radio);
            v1 = Vect(p.getX(),p.getY(),p.getZ());
            v2 = Vect(0,i*h-h/2,0);
            v = v1 - v2;
            nodo = new Nodo(p);
            nodo->setNormal(v); //le seteamos su normal
            nodo->setConcentracion(0.0); // le seteamos su concentracion
            nodos->addNodo(nodo);
        }
    }

    arcos = new Arcos();
    caras = new Caras();
    int n0, n1, n2, n3;

    for(int i=0; i<num_anillos-1; i++) {
        for(int j=0; j<num_puntos; j++) {

            n0 = num_puntos*i+j;
            n1 = num_puntos*i+((j+1)%num_puntos);
            n2 = num_puntos*(i+1)+j;
            n3 = num_puntos*(i+1)+((j+1)%num_puntos);

            if (i%2==0){  //Para que se vayan alternando los arcos.
                arcos->addArco(new Arco(n0, n1));
                arcos->addArco(new Arco(n0, n2));
                arcos->addArco(new Arco(n0, n3));
                caras->addCara(new Triangulo(n0,n3,n1));
                caras->addCara(new Triangulo(n0,n2,n3));
                }
            else{
                arcos->addArco(new Arco(n0, n1));
                arcos->addArco(new Arco(n0, n2));
                arcos->addArco(new Arco(n1, n2));
                caras->addCara(new Triangulo(n1,n2,n3));
                caras->addCara(new Triangulo(n0,n2,n1));
                }

            if(i==num_anillos-2)    //Generamos los arcos del borde superior.
                arcos->addArco(new Arco(n2, n3));

            }
        }

    updateVecinos();

    Malla *malla = new MallaTriangulos(nodos,arcos,caras);
    malla->setMedula(medula);
    malla->setConcentracionMax(1.0);
    malla->setConcentracionMin(0.0);
    assert(malla->checkMalla(true) >= 0);

    return malla;
}

void GeneraCilindro::updateVecinos(){
    //Actualizo arcos vecinos de los nodos.
    int numarcos=arcos->getNumArcos();
    for (int iarco=0; iarco<numarcos; iarco++){
        nodos->getNodo(arcos->getArco(iarco)->getNodo1())->addArco(iarco);
        nodos->getNodo(arcos->getArco(iarco)->getNodo2())->addArco(iarco);
        }

    //Actualizo caras vecinas de los nodos.
    int numcaras=caras->getNumCaras();
    for (int icara=0; icara<numcaras; icara++){
        Cara *c=caras->getCara(icara);
        for(int j=0; j<c->getNumElem();++j)
            nodos->getNodo(c->getNodos()[j])->addCara(icara);
        }

    //Actualizo arcos vecinos de las caras y caras vecinas de los arcos
    vector<int> nodosCara;
    vector<int> arcosARevisar;

    for (int icara=0; icara<numcaras; icara++){
        Cara *c=caras->getCara(icara);
        nodosCara=c->getNodos();

        for(int j=0; j<c->getNumElem();++j) {
            arcosARevisar=nodos->getNodo(nodosCara[j])->getArcos();
            for(int iarco=0; iarco<(int)arcosARevisar.size(); iarco++)
                if(arcos->getArco(arcosARevisar[iarco])->estanNodos(nodosCara)){
                    caras->getCara(icara)->addArco(arcosARevisar[iarco]);
                    arcos->getArco(arcosARevisar[iarco])->setCara(icara);
                    }
            }

        }

    }

Malla* GeneraCilindro::generaMallaCuadrilateros() {
    //Genero la medula.
    vector<Punto> medula;
    medula.push_back(Punto(0,0,0));
    medula.push_back(Punto(0,altura,0));

    int num_nodos = num_anillos * num_puntos;

    Nodos *nodos = new Nodos();
    Nodo *nodo;
    Punto p;
    Vect v, v1, v2;

    double h,angulo;
    h = altura / num_anillos;
    angulo = 2*PI / num_puntos;
    for(int i=0; i<num_anillos; i++) {
        for(int j=0; j<num_puntos; j++) {
            p = Punto(cos(j*angulo)*radio,i*h-h/2,sin(j*angulo)*radio);
            v1 = Vect(p);
            v2 = Vect(0,i*h-h/2,0);
            v = v1 - v2;
            nodo = new Nodo(p);
            nodo->setNormal(v); //le seteamos su normal
            nodo->setConcentracion(0.0); // le seteamos su concentracion
            nodos->addNodo(nodo);
        }
    }

    Arco *a;
    Arcos *arcos = new Arcos();
    Cara *c;
    Caras *caras = new Caras();

    int ind_cara, ind_arco;
    int n1, n2, n3, n4;
    vector<int> ind_nodos;
    vector<int> ind_arcos;
    for(int i=0; i<(num_anillos-1); i++) {
        for(int j=0; j<num_puntos; j++) {
            ind_nodos.clear();
            ind_arcos.clear();
            // Orden: n1 n2 n3 n4 <-> SE SO NO NE
            n1 = int(fmod(num_puntos*i+j,num_nodos));
            n4 = int(fmod(num_puntos*(i+1)+j,num_nodos));
            if(j == num_puntos-1) {
                n2 = n1-num_puntos+1;
                n3 = n4-num_puntos+1;
            }
            else {
                n2 = int(fmod(num_puntos*i+j+1,num_nodos));
                n3 = int(fmod(num_puntos*(i+1)+j+1,num_nodos));
            }
            // Orden inverso para tener normal saliente
            ind_nodos.push_back(n4);
            ind_nodos.push_back(n3);
            ind_nodos.push_back(n2);
            ind_nodos.push_back(n1);
            if(i == num_anillos-2) {
                if(j == 0) {
                    ind_arcos.push_back(2*(n1-1)+3*num_puntos);
                }
                else {
                    ind_arcos.push_back(2*n1+j-2);
                }
                ind_arcos.push_back(2*n1+j);
                ind_arcos.push_back(2*n1+j+1);
                ind_arcos.push_back(2*(n1+1)+j);
            }
            else {
                if(j == 0) {
                    ind_arcos.push_back(2*(n1+num_puntos)-1);
                }
                else {
                    ind_arcos.push_back(2*n1-1);
                }
                ind_arcos.push_back(2*n1);
                ind_arcos.push_back(2*n1+1);
                if(i == num_anillos-3) {
                    ind_arcos.push_back(2*n1+2*num_puntos+j);
                }
                else {
                    ind_arcos.push_back(2*n1+2*num_puntos);
                }
            }
            c = new Cuadrilatero(ind_nodos,ind_arcos);
            ind_cara = caras->addCara(c);

            nodos->addCaraNodo(n1,ind_cara);
            nodos->addCaraNodo(n2,ind_cara);
            nodos->addCaraNodo(n3,ind_cara);
            nodos->addCaraNodo(n4,ind_cara);

            int ind_cara2 = -1;
            if(i != 0) {
                ind_cara2 = ind_cara-num_puntos;
            }

            a = new Arco(n1,n2,ind_cara,ind_cara2);
            ind_arco = arcos->addArco(a);
            nodos->addArcoNodo(n1,ind_arco);
            nodos->addArcoNodo(n2,ind_arco);

            ind_cara2 = ind_cara+1;
            if(j == num_puntos-1) {
                ind_cara2 = ind_cara-num_puntos+1;
            }

            a = new Arco(n2,n3,ind_cara,ind_cara2);
            ind_arco = arcos->addArco(a);
            nodos->addArcoNodo(n2,ind_arco);
            nodos->addArcoNodo(n3,ind_arco);

            if(i == num_anillos-2) {
                if(j == num_puntos-1) {
                    a = new Arco(int(fmod(n1+num_puntos,num_nodos)),int(fmod(n1+1,num_nodos)),ind_cara,-1);
                    ind_arco = arcos->addArco(a);
                    nodos->addArcoNodo(int(fmod(n1+num_puntos,num_nodos)),ind_arco);
                    nodos->addArcoNodo(int(fmod(n1+1,num_nodos)),ind_arco);
                }
                else {
                    a = new Arco(int(fmod(n1+num_puntos,num_nodos)),int(fmod(n1+num_puntos+1,num_nodos)),ind_cara,-1);
                    ind_arco = arcos->addArco(a);
                    nodos->addArcoNodo(int(fmod(n1+num_puntos,num_nodos)),ind_arco);
                    nodos->addArcoNodo(int(fmod(n1+num_puntos+1,num_nodos)),ind_arco);
                }
            }
        }
    }

    Malla *malla = new MallaCuadrilateros(nodos,arcos,caras);
    malla->setMedula(medula);
    malla->setConcentracionMax(1.0);
    malla->setConcentracionMin(0.0);
    assert(malla->checkMalla(true) >= 0);

    return malla;
}
