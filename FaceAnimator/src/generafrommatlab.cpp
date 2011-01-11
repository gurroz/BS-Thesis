#include "generafrommatlab.h"

GeneraFromMatLab::GeneraFromMatLab(string arch, int num_anillos, int num_puntos, int tipo):AlgGeneracion() {
    this->archivo = arch;
    this->num_anillos = num_anillos;
    this->num_puntos = num_puntos;
    this->tipo = tipo;
}

Malla* GeneraFromMatLab::aplicar() {
    if(this->tipo == 0) {
        return this->generaMallaTriangulos();
    }
    else {
        return this->generaMallaCuadrilateros();
    }
}

/*
* Genera una malla de triángulos desde un archivo en formato MatLab.
* El archivo se divide en cuatro grupos de filas: primero todas las
* coordenadas x, luego todas las coordenadas z, luego las coordenadas y
* y finalmente las concentraciones en los nodos.
*/
Malla* GeneraFromMatLab::generaMallaTriangulos() {
	//Lineas necesarias para que scanf lea archivo en computadores seteados en otro lenguaje.
	setlocale(LC_NUMERIC, "POSIX");

    FILE *mat = fopen(archivo.c_str(),"r");
    float flt;
    if(num_anillos == 0) {
        FILE *mat2 = fopen(archivo.c_str(),"r");
        if(num_puntos == 0) {
            num_puntos = 90;
        }
        int num = 0;
        while(fscanf(mat2,"%f\n",&flt) != EOF) {
            num++;
        }
        num_anillos = num/(4*num_puntos);
		fclose(mat2);
    }
    int num_nodos = num_anillos * num_puntos; // número de nodos de la malla

    Nodos *nodos = new Nodos();
    Nodo *nodo;
    Punto p;
    double max_concentracion = 0.0;
    double min_concentracion = 99999999.0;
    // Generamos los nodos de la malla, con la información en el archivo.
    for(int j=0; j<4; j++) {
        for(int i=0; i<num_nodos; i++) {
            fscanf(mat,"%f\n",&flt);
            if(j == 0) {
                p = Punto(flt,0,0);
                nodo = new Nodo(p);
                nodos->addNodo(nodo);
            }

            //Invierto Y y Z para que se despliegue correctamente en la aplicacion.
            else if(j == 1) {
                Punto aux=nodos->getNodo(i)->getPunto();
                aux.setZ(flt);
                nodos->getNodo(i)->setPunto(aux);
            }
            else if(j == 2) {
                Punto aux=nodos->getNodo(i)->getPunto();
                aux.setY(flt);
                nodos->getNodo(i)->setPunto(aux);
            }
            else {
                if(flt < min_concentracion) {
                    min_concentracion = flt;
                }
                if(flt > max_concentracion) {
                    max_concentracion = flt;
                }
                nodos->getNodo(i)->setConcentracion(flt);
            }
        }
    }

    // ahora formamos los arcos y caras.
    Arco *a;
    Arcos *arcos = new Arcos();
    Cara *c;
    Caras *caras = new Caras();

    int ind_cara1, ind_cara2, ind_arco;
    int n1, n2, n3, n4;
    int a1, a2, a3;
    vector<int> ind_nodos;
    vector<int> ind_arcos;
    for(int i=0; i<(num_anillos-1); i++) {
        for(int j=0; j<num_puntos; j++) {

            ind_nodos.clear();
            ind_arcos.clear();

            //se deben generar 2 caras.
            //cara1: n1 n2 n3
            //cara2: n1 n3 n4
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

            ind_nodos.push_back(n3);
            ind_nodos.push_back(n2);
            ind_nodos.push_back(n1);

            a1 = 3*(i*num_puntos+j);
            if(i == num_anillos-2) {
                a1 = 3*i*num_puntos+4*j;
            }
            a2 = a1+1;
            a3 = a1+2;

            ind_arcos.push_back(a1);
            ind_arcos.push_back(a2);
            ind_arcos.push_back(a3);

            c = new Triangulo(ind_nodos,ind_arcos);
            ind_cara1 = caras->addCara(c);

            nodos->addCaraNodo(n1,ind_cara1);
            nodos->addCaraNodo(n2,ind_cara1);
            nodos->addCaraNodo(n3,ind_cara1);

            ind_nodos.clear();
            ind_arcos.clear();

            ind_nodos.push_back(n4);
            ind_nodos.push_back(n3);
            ind_nodos.push_back(n1);

            a1 = 3*(i*num_puntos+j)+2;
            if(i == num_anillos-2) {
                a1 = 3*i*num_puntos+4*j+2;
            }
            a2 = 3*(i+1)*num_puntos+3*j;
            if(i == num_anillos-3) {
                a2 = 3*(i+1)*num_puntos+4*j;
            }
            else if(i == num_anillos-2) {
                a2 = a1+1;
            }
            a3 = a1 - 4;
            if(i == num_anillos-2) {
                if(j==0) {
                    a3 = a1+4*(num_puntos-1)-1;
                }
                else {
                    a3 = a1-5;
                }
            }
            else {
                if(j==0) {
                    a3 = a1+3*(num_puntos-1)-1;
                }
            }

            ind_arcos.push_back(a1);
            ind_arcos.push_back(a2);
            ind_arcos.push_back(a3);

            c = new Triangulo(ind_nodos,ind_arcos);
            ind_cara2 = caras->addCara(c);

            nodos->addCaraNodo(n1,ind_cara2);
            nodos->addCaraNodo(n3,ind_cara2);
            nodos->addCaraNodo(n4,ind_cara2);

            int ind_cara3 = -1;
            if(i != 0) {
                ind_cara3 = ind_cara1-(2*num_puntos)+1;
            }

            a = new Arco(n1,n2,ind_cara1,ind_cara3);
            ind_arco = arcos->addArco(a);
            nodos->addArcoNodo(n1,ind_arco);
            nodos->addArcoNodo(n2,ind_arco);

            ind_cara3 = ind_cara1+3;
            if(j == num_puntos-1) {
                ind_cara3 = ind_cara1-2*(num_puntos-1)+1;
            }

            a = new Arco(n2,n3,ind_cara1,ind_cara3);
            ind_arco = arcos->addArco(a);
            nodos->addArcoNodo(n2,ind_arco);
            nodos->addArcoNodo(n3,ind_arco);

            a = new Arco(n1,n3,ind_cara1,ind_cara2);
            ind_arco = arcos->addArco(a);
            nodos->addArcoNodo(n1,ind_arco);
            nodos->addArcoNodo(n3,ind_arco);

            if(i == num_anillos-2) {
                if(j == num_puntos-1) {
                    a = new Arco(int(fmod(n1+num_puntos,num_nodos)),int(fmod(n1+1,num_nodos)),ind_cara2,-1);
                    ind_arco = arcos->addArco(a);
                    nodos->addArcoNodo(int(fmod(n1+num_puntos,num_nodos)),ind_arco);
                    nodos->addArcoNodo(int(fmod(n1+1,num_nodos)),ind_arco);
                }
                else {
                    a = new Arco(int(fmod(n1+num_puntos,num_nodos)),int(fmod(n1+num_puntos+1,num_nodos)),ind_cara2,-1);
                    ind_arco = arcos->addArco(a);
                    nodos->addArcoNodo(int(fmod(n1+num_puntos,num_nodos)),ind_arco);
                    nodos->addArcoNodo(int(fmod(n1+num_puntos+1,num_nodos)),ind_arco);
                }
            }
        }
    }

    Malla *malla = new MallaTriangulos(nodos,arcos,caras);
    malla->setConcentracionMax(max_concentracion);
    malla->setConcentracionMin(min_concentracion);
    malla->setNormales();

	fclose(mat);
	setlocale(LC_NUMERIC, "");

	//Chequeamos consistencia topologica.
	int V=malla->getNumNodos();
	int E=malla->getNumArcos();
	int F=malla->getNumCaras();
	cout << "Numero de nodos=" << V << endl;
	cout << "Numero de arcos=" << E << endl;
	cout << "Numero de caras=" << F << endl;
	if (V-E+F==2 || V-E+F==0)
		cout << "La malla es consistente. Cumple la formula de Euler: V-E+F=2" << endl;
	else
		cout << "Atencion, la malla no es consistente. No cumple la formula de Euler: V-E+F=" << V-E+F << " y deberia ser V-E+F=2" << endl;

    assert(malla->checkMalla(true) >= 0);
    return malla;
}

Malla* GeneraFromMatLab::generaMallaCuadrilateros() {
	//Lineas necesarias para que scanf lea archivo en computadores seteados en otro lenguaje.
	setlocale(LC_NUMERIC, "POSIX");

    FILE *mat = fopen(archivo.c_str(),"r");
    float flt;
    if(num_anillos == 0) {
        FILE *mat2 = fopen(archivo.c_str(),"r");
        if(num_puntos == 0) {
            num_puntos = 90;
        }
        int num = 0;
        while(fscanf(mat2,"%f\n",&flt) != EOF) {
            num++;
        }
        num_anillos = num/(4*num_puntos);
		fclose(mat2);
    }
    int num_nodos = num_anillos * num_puntos; // número de nodos de la malla

    Nodos *nodos = new Nodos();
    Nodo *nodo;
    Punto p;
    double max_concentracion = 0.0;
    double min_concentracion = 99999999.0;
    // Generamos los nodos de la malla, con la información en el archivo.
    for(int j=0; j<4; j++) {
        for(int i=0; i<num_nodos; i++) {
            fscanf(mat,"%f\n",&flt);
            if(j == 0) {
                p = Punto(flt,0,0);
                nodo = new Nodo(p);
                nodos->addNodo(nodo);
            }
            else if(j == 1) {
                Punto aux=nodos->getNodo(i)->getPunto();
                aux.setZ(flt);
                nodos->getNodo(i)->setPunto(aux);
            }
            else if(j == 2) {
                Punto aux=nodos->getNodo(i)->getPunto();
                aux.setY(flt);
                nodos->getNodo(i)->setPunto(aux);
            }
            else {
                if(flt < min_concentracion) {
                    min_concentracion = flt;
                }
                if(flt > max_concentracion) {
                    max_concentracion = flt;
                }
                nodos->getNodo(i)->setConcentracion(flt);
            }
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
    malla->setConcentracionMax(max_concentracion);
    malla->setConcentracionMin(min_concentracion);
    malla->setNormales();

	fclose(mat);
	setlocale(LC_NUMERIC, "");

	//Chequeamos consistencia topologica.
	int V=malla->getNumNodos();
	int E=malla->getNumArcos();
	int F=malla->getNumCaras();
	cout << "Numero de nodos=" << V << endl;
	cout << "Numero de arcos=" << E << endl;
	cout << "Numero de caras=" << F << endl;
	if (V-E+F==2 || V-E+F==0)
		cout << "La malla es consistente. Cumple la formula de Euler: V-E+F=2" << endl;
	else
		cout << "Atencion, la malla no es consistente. No cumple la formula de Euler: V-E+F=" << V-E+F << " y deberia ser V-E+F=2" << endl;

    assert(malla->checkMalla(true) >= 0);
    return malla;
}
