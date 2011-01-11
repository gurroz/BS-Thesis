#include "generafromwfm.h"

#include <fstream>
#include <sstream>
#include <map>

#define MAXLINE	256


GeneraFromWFM::GeneraFromWFM(string arch_x):AlgGeneracion() {
    archivo = arch_x;
}

Malla* GeneraFromWFM::aplicar() {
	int n_triangulos = 0, n_cuadrilateros = 0; // cantidad de caras de tres y cuatro lados
	ifstream in(archivo.c_str());
	char line[MAXLINE];

    string cx,cy,cz;
	float x,y,z;

    int num_puntos, num_caras;

    num_puntos=0;
    Nodos *nodos = new Nodos();
    Nodo *nodo;

    while(true){
        in.getline(line,MAXLINE);
		if (line[0]!='#' && line[0]!= 13){
            stringstream streamin(line);
            streamin >> num_puntos;
			break;
		}
    }

    for(int i = 0; i< num_puntos; ++i) {
        in.getline(line,MAXLINE);
		stringstream streamin(line);

		streamin >> x;
		streamin >> y;
		streamin >> z;

        nodo = new Nodo(Punto(x,y,z));
        nodos->addNodo(nodo);
    }

    map<pair<int,int>,int> ind_arcos;
    map<pair<int,int>,int>::iterator iter1;
	map<pair<int,int>,int>::iterator iter2;
    vector<int> indice_puntos;
    vector<int> indice_arcos;
    Arcos *arcos = new Arcos();
    Caras *caras = new Caras();
    Cara *c;
    int indice;

    int indices[4], n_lados;
    num_caras=0;


    while(true){
        in.getline(line,MAXLINE);
		if (line[0]!='#' && line[0]!= 13){
            stringstream streamin(line);
            streamin >> num_caras;
			break;
		}
    }
    cerr << "num_caras=" << num_caras << endl;
    for(int n=0; n<num_caras; ++n) {
        indices[3]=-1;
		in.getline(line,MAXLINE);
		if (in.fail())
            break;
		stringstream streamin(line);
		for(int i=0; i<4; i++)
            streamin >> indices[i];

        if(indices[3] == -1) {
        	n_triangulos++;
            n_lados = 3;
        }
        else {
        	n_cuadrilateros++;
            n_lados = 4;
        }

        for(int i=0; i<n_lados; i++)
            indice_puntos.push_back(indices[i]);

        for(int j=0; j<n_lados; j++) {
            int ind1 = indice_puntos[j];
            int ind2 = indice_puntos[int(fmod(j+1,n_lados))];
            pair<int,int> pr1(ind1,ind2);
			pair<int,int> pr2(ind2,ind1);
            iter1 = ind_arcos.find(pr1);
			iter2 = ind_arcos.find(pr2);
            if(iter1 != ind_arcos.end())
                indice_arcos.push_back(iter1->second);
            else if(iter2 != ind_arcos.end())
                indice_arcos.push_back(iter2->second);
            else {
                indice = arcos->addArco(new Arco(ind1,ind2));
                indice_arcos.push_back(indice);
                ind_arcos.insert(make_pair(pr1,indice));
                nodos->addArcoNodo(ind1,indice);
                nodos->addArcoNodo(ind2,indice);
            }
        }
        if(n_lados == 3)
            c = new Triangulo(indice_puntos,indice_arcos);
        else if(n_lados == 4)
            c = new Cuadrilatero(indice_puntos,indice_arcos);
        else
            c = new Cara(indice_puntos,indice_arcos);

        int ind_cara = caras->addCara(c);
        for(int j=0; j<n_lados; j++) {
            arcos->setCaraArco(indice_arcos[j],ind_cara);
            nodos->addCaraNodo(indice_puntos[j],ind_cara);
        }
        indice_puntos.clear();
        indice_arcos.clear();
    }

	Malla *malla = 0;
    if(n_cuadrilateros == 0)
    	malla = new MallaTriangulos(nodos,arcos,caras);
	else if(n_triangulos == 0)
		malla = new MallaCuadrilateros(nodos,arcos,caras);
	else
		malla = new Malla(nodos,arcos,caras);
	malla->setConcentracionTodos(1.0);
    malla->setConcentracionMax(1.0);
    malla->setConcentracionMin(0.0);
    malla->setNormales();
    //malla->setTextura(LoadGLTexture("Textura.bmp"));

	in.close();

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
    cout << endl;

    return malla;
}
