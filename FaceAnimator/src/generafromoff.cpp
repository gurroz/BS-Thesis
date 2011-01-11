#include "generafromoff.h"

GeneraFromOFF::GeneraFromOFF(string arch):AlgGeneracion() {
    archivo = arch;
}

Malla* GeneraFromOFF::aplicar() {
	int n_triangulos = 0, n_cuadrilateros = 0; // cantidad de caras de tres y cuatro lados
	//Lineas necesarias para que scanf lea archivo en computadores seteados en otro lenguaje.
	setlocale(LC_NUMERIC, "POSIX");

    FILE *off = fopen(archivo.c_str(),"r");

    char line[255];
    int num_puntos, num_caras, num_arcos;
    float x,y,z;
    fscanf(off,"%s\n",line);
	while(true){
		fgets(line,255,off);
		if (line[0]!='#')break;
		}
    sscanf(line,"%d %d %d\n",&num_puntos,&num_caras,&num_arcos);
    Nodos *nodos = new Nodos();
    Nodo *nodo;
    for(int i=0; i<num_puntos; i++) {
        fscanf(off,"%f %f %f\n",&x,&y,&z);
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
    int tipo_cara;
    int indice;
    float r,g,b;
    char resto[256];
    int ch;
    for(int i=0; i<num_caras; i++) {
        fscanf(off,"%d",&tipo_cara);
        for(int j=0; j<tipo_cara; j++) {
            fscanf(off,"%d",&indice);
            indice_puntos.push_back(indice);
        }
        ch = fgetc(off);
        int k=0;
        while(ch != '\n' ) {
            resto[k++] = ch;
            ch = fgetc(off);
        }
        resto[k] = '\0';
        int num_colores = sscanf(resto,"%f %f %f\n",&r,&g,&b);
        if(num_colores == 0) {
            cout << "Error: " << resto << " no se puede parsear." << endl;
            assert(1 == 0);
        }
        else {
            if(num_colores != 3) {
                r=-1;
                g=-1;
                b=-1;
            }
        }

        for(int j=0; j<tipo_cara; j++) {
            int ind1 = indice_puntos[j];
            int ind2 = indice_puntos[int(fmod(j+1,tipo_cara))];
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
        if(tipo_cara == 3)
            c = new Triangulo(indice_puntos,indice_arcos);
        else if(tipo_cara == 4)
            c = new Cuadrilatero(indice_puntos,indice_arcos);
        else
            c = new Cara(indice_puntos,indice_arcos);
        c->setColores(r,g,b);
        int ind_cara = caras->addCara(c);
        for(int j=0; j<tipo_cara; j++) {
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

	fclose(off);
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
