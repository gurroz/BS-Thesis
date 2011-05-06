#include "movimientosFromFile.h"

#include <fstream>
#include <sstream>
#define MAXLINE	256

MovimientosFromFile::MovimientosFromFile(string filename): AlgDesplazamientoMallaTriangulos(){
    N = 11;
    sizes = new int[N];
    nodes = new int*[N];
    values = new float**[N];


    ifstream in(filename.c_str());
	char line[MAXLINE];

    int nodo;
	float x,y,z;

    int count = 0;
    while(true){
        in.getline(line,MAXLINE);
        string str(line);
        if(str.find("ANIMATION UNITS LIST") != string::npos){
            in.getline(line, MAXLINE);
            break;
        }
        if(in.fail()){
            in.close();
            return;
        }
    }

    while(true){
        in.getline(line,MAXLINE);
        string str(line);
		if (in.fail())
            break;
        if(str.find("#") == 0){

            in.getline(line,MAXLINE);

            if(line[0] == '#' || line[1] == '#'){
                break;
            }

            stringstream streamin(line);
            int size;
            streamin >> size;
            sizes[count] = size;

            nodes[count] = new int[size];
            values[count] = new float*[size];

            for(int i = 0; i< size; ++i){
                values[count][i] = new float[3];
                in.getline(line,MAXLINE);
                string number(line);
                stringstream streamin(line);

                streamin >> nodo;
                streamin >> x;
                streamin >> y;
                streamin >> z;
                nodes[count][i] = nodo;
                values[count][i][0] = x;
                values[count][i][1] = y;
                values[count][i][2] = z;
            }
            count++;
        }
    }

    in.close();

};

MovimientosFromFile::~MovimientosFromFile(){
    for(int i = 0; i < N; ++i){
        delete[] nodes[i];
        for(int j = 0; j < sizes[i]; ++j){
            delete[] values[i][j];
        }
        delete[] values[i];
    }
    delete[] sizes;
    delete[] nodes;
    delete[] values;
};

void MovimientosFromFile::aplicar(Malla *malla) {
return;
}

void MovimientosFromFile::moverNodosSegunParametro(int indice, double valor, Malla *malla){

    int nNodos = malla->getMaxIndiceNodos();
    double xs[nNodos +1];
    double ys[nNodos +1];
    double zs[nNodos +1];

    for(int i = 0; i <= nNodos; ++i){
        xs[i] = 0.0;
        ys[i] = 0.0;
        zs[i] = 0.0;
    }

    for(int i = 0; i < malla->getNodos()->n_marcados; ++i){
        Punto *p = this->getMovimiento(i, indice);
        int ind = malla->getNodos()->nodos_marcados[i];
        xs[ind] = p->getX();
        ys[ind] = p->getY();
        zs[ind] = p->getZ();
    }

    for(int i = 0; i <= nNodos; ++i){
        Nodo *n = malla->getNodo(i);
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

Punto *MovimientosFromFile::getMovimiento(int number_nodo, int indice_unit){
    for(int i = 0; i < sizes[indice_unit]; ++i){
        if (nodes[indice_unit][i] == number_nodo){
            return new Punto(values[indice_unit][i][0], values[indice_unit][i][1], values[indice_unit][i][2]);
        }
    }
    return new Punto(0.0, 0.0, 0.0);
}
