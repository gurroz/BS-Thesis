#include "generafromarchivosxyzu.h"
#include <stdio.h>
#include <string.h>



GeneraFromArchivosXYZU::GeneraFromArchivosXYZU(string arch_x, string arch_y, string arch_z, string arch_u):AlgGeneracion() {
    archivo_x = arch_x;
    archivo_y = arch_y;
    archivo_z = arch_z;
    archivo_u = arch_u;
}

Malla* GeneraFromArchivosXYZU::aplicar() {
	int n_triangulos = 0, n_cuadrilateros = 0; // cantidad de caras de tres y cuatro lados
	//Lineas necesarias para que scanf lea archivo en computadores seteados en otro lenguaje.
	setlocale(LC_NUMERIC, "POSIX");

    FILE *arch_x = fopen(archivo_x.c_str(),"r");
    FILE *arch_y = fopen(archivo_y.c_str(),"r");
    FILE *arch_z = fopen(archivo_z.c_str(),"r");
    FILE *arch_u = fopen(archivo_u.c_str(),"r");

    char line[50];
    char cx[16];
    char cy[16];
    char cz[16];
    int num_puntos, num_caras;
    float x,y,z,nx,ny,nz,u;
    fscanf(arch_x,"%s %s\n",line,line);
    fscanf(arch_y,"%s %s\n",line,line);
    fscanf(arch_z,"%s %s\n",line,line);
    fscanf(arch_u,"%s %s\n",line,line);

    num_puntos=0;
    Nodos *nodos = new Nodos();
    Nodo *nodo;
    while(true) {
        fscanf(arch_x,"%s %s %s\n",cx,cy,cz);
        fscanf(arch_y,"%s %s %s\n",cx,cy,cz);
        fscanf(arch_z,"%s %s %s\n",cx,cy,cz);
        fscanf(arch_u,"%s %s %s\n",cx,cy,cz);
        if(strcmp(cx,"%") == 0) {
            break;
        }
        sscanf(cx,"%f",&x);
        sscanf(cy,"%f",&y);
        sscanf(cz,"%f",&z);
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
    char *token;

    int indices[4];
    int n_lados;
    num_caras=0;
    while(true) {
        fgets(line, 50, arch_x);
        fgets(line, 50, arch_y);
        fgets(line, 50, arch_z);
        fgets(line, 50, arch_u);
        if(strpbrk("%",line) != NULL) {
            break;
        }
        token = strtok(line," ");
        for(int i=0; i<3; ++i) {
            sscanf(token,"%d",&indices[i]);
            token = strtok(NULL, " ");
        }
        if(token == NULL) { // Caso triángulos
        	n_triangulos++;
            n_lados = 3;
        }
        else { // Caso cuadriláteros
            sscanf(token,"%d",&indices[3]);
            n_cuadrilateros++;
            n_lados = 4;
        }

        //Nota: Por bug en los archivos de entrada, debo invertir el orden para que las normales queden bien.
        //for(int i=n_lados-1; i>=0; --i) // invertido por bug archivo entrada
        for(int i=0; i<n_lados; ++i) // así debiera ser
            indice_puntos.push_back(indices[i]-1);

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
        else // n_lados == 4
            c = new Cuadrilatero(indice_puntos,indice_arcos);
        int ind_cara = caras->addCara(c);
        num_caras++;
        for(int j=0; j<n_lados; j++) {
            arcos->setCaraArco(indice_arcos[j],ind_cara);
            nodos->addCaraNodo(indice_puntos[j],ind_cara);
        }
        indice_puntos.clear();
        indice_arcos.clear();
    }

    float max_concentracion = 0;
    float min_concentracion = 999999999;
    for(int i=0; i<num_puntos; i++) {
        fscanf(arch_x,"%f\n",&nx);
        fscanf(arch_y,"%f\n",&ny);
        fscanf(arch_z,"%f\n",&nz);
        fscanf(arch_u,"%f\n",&u);

        if(u < min_concentracion) {
            min_concentracion = u;
        }
        if(u > max_concentracion) {
            max_concentracion = u;
        }

        Vect normal = Vect(nx,ny,nz);
        nodos->getNodo(i)->setNormal(normal);
        nodos->getNodo(i)->setConcentracion(u);
    }

    cout << "max_concentracion = " << max_concentracion << endl;
    cout << "min_concentracion = " << min_concentracion << endl;

    Malla *malla = 0;
    if(n_cuadrilateros == 0)
    	malla = new MallaTriangulos(nodos,arcos,caras);
	else if(n_triangulos == 0)
		malla = new MallaCuadrilateros(nodos,arcos,caras);
	else
		malla = new Malla(nodos,arcos,caras);
    malla->setConcentracionMax(max_concentracion);
    malla->setConcentracionMin(min_concentracion);

	fclose(arch_x);
	fclose(arch_y);
	fclose(arch_z);
	fclose(arch_u);
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
		cout << "Atencion, la malla no es consistente. No cumple la formula de Euler: V(" << V << ")-E(" << E << "+F("<< F << ")=" << V-E+F << " y deberia ser V-E+F=2" << endl;

    assert(malla->checkMalla(true) >= 0);
    return malla;

}
