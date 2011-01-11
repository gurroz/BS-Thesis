#include "generafromwrl.h"

#include <sstream>
#include <map>

#define MAXLINE	256


GeneraFromWRL::GeneraFromWRL(string arch_x):AlgGeneracion() {
    archivo = arch_x;
}

Malla *GeneraFromWRL::getMallaFromFile(ifstream *in){
    int n_triangulos = 0, n_cuadrilateros = 0; // cantidad de caras de tres y cuatro lados
    char line[MAXLINE];

    string cx,cy,cz;
	float x,y,z;

    int num_puntos, num_caras;

    GLuint textura;

    num_puntos=0;
    Nodos *nodos = new Nodos();
    Nodo *nodo;
    int ppp = 0;
    while(true){
        in->getline(line,MAXLINE);
        string str(line);
        /*if(ppp < 100) ++ppp;
        else
        break;*/
        if(str.find("point [") != string::npos){
                break;
        }

        if(str.find("ImageTexture") != string::npos){
            size_t pos = str.find("url");
            while(pos == string::npos){
                in->getline(line,MAXLINE);
                str = string(line);
                pos = str.find("url");
            }
            pos = str.find("\"");
            while(pos == string::npos){
                in->getline(line,MAXLINE);
                str = string(line);
                pos = str.find("url");
            }
            size_t final_pos = str.find("\"", pos + 1);
            string name = str.substr(pos + 1, final_pos - pos - 1);


            int indice_bar = archivo.find_last_of("/") + 1;
            stringstream file_name_tex;
            file_name_tex << archivo.substr(0, indice_bar) << name;
            textura = LoadGLTexture(file_name_tex.str().c_str());
        }

        if(in->fail())
            return NULL;
    }
    for(int i = 0; true; ++i) {
        in->getline(line,MAXLINE);
        string str(line);
        if(str.find("coordIndex")!= string::npos){
                break;
        }

		stringstream streamin(line);

		streamin >> x;
		streamin >> y;
		streamin >> z;

        nodo = new Nodo(Punto(x,y,z));
        nodos->addNodo(nodo);

        num_puntos++;
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


    for(int n=0; true; ++n) {
        indices[3]=-1;
		in->getline(line,MAXLINE);
		if (in->fail())
            break;
		stringstream streamin(line);
		char ch;
		for(int i=0; true; i++){
            streamin >> indices[i];
            streamin >> ch;
            if(indices[i] == -1)
                break;
		}


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
		if(ch == ']'){
		    break;
		}
    }

    //texCoord TextureCoordinate { point [
    for(int n=0; true; ++n) {
		in->getline(line,MAXLINE);
		if (in->fail())
            break;
        string str(line);

        if(str.find("TextureCoordinate") != string::npos)
            break;
    }

    for(int i = 0; i < nodos->getNumNodos(); ++i) {
        double d1, d2;
        in->getline(line,MAXLINE);
        string str(line);
        if(str.find("{") != string::npos)
            str.replace(str.find("{"),1, "(");

		stringstream streamin(line);

		streamin >> d1;
		streamin >> d2;

        nodos->getNodo(i)->setTexturePoint(d1, d2);

		if(str.find("]") != string::npos){
            break;
		}

    }
    //std::cout << "TOTAL=" << nodos->getNumNodos() << endl;



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

    malla->setTextura(textura);

    return malla;
}


Malla* GeneraFromWRL::aplicar() {
    cout << "archivo =" << archivo << endl;

	ifstream in(archivo.c_str());

	Malla *malla = getMallaFromFile(&in);
	Malla *m = malla;
	Malla *m1 = getMallaFromFile(&in);
	while(m1 != NULL){
	    m->setNextMalla(m1);
	    m = m1;
	    m1 = getMallaFromFile(&in);
	}

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
    return malla;
    return malla;
}
