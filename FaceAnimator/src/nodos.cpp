#include "nodos.h"
#include <limits>

Nodos::Nodos() {
    num_nodos = 0;
    num_nodos_validos = 0;
    minx = numeric_limits<float>::max();
    maxx = -1*numeric_limits<float>::max();
    miny = numeric_limits<float>::max();
    maxy = -1*numeric_limits<float>::max();
    minz = numeric_limits<float>::max();
    maxz = -1*numeric_limits<float>::max();

    nodos_marcados = NULL;
}

Nodos::Nodos(vector<Nodo*> nds) {
    num_nodos = nds.size();
    num_nodos_validos = nds.size();
    nodos = nds;
    double mx = -1*numeric_limits<float>::max();
    double mix = numeric_limits<float>::max();
    double my = -1*numeric_limits<float>::max();
    double miy = numeric_limits<float>::max();
    double mz = -1*numeric_limits<float>::max();
    double miz = numeric_limits<float>::max();
    for(int i = 0; i < (int)nds.size(); ++i){
        Nodo* n = nds[i];
		if( n!= 0){
		    Punto p = n->getPunto();
		    double x = p.getX();
		    double y = p.getY();
		    double z = p.getZ();
		    if(x>mx) mx = x;
		    if(x<mix) mix = x;
		    if(y>my) my = y;
		    if(y<miy) miy = y;
		    if(z>mz) mz = z;
		    if(z<miz) miz = z;
		}
    }
    this->maxx = mx;
    this->minx = mix;
    this->maxy = my;
    this->miny = miy;
    this->maxz = mz;
    this->minz = miz;

    nodos_marcados = NULL;
}

Nodos::Nodos(Nodos *n) {
	vector<Nodo*> nuevos_nodos;
	for(int i = 0; i < (int)n->nodos.size(); ++i)
		if(n->nodos[i] != 0)
			nuevos_nodos.push_back(n->nodos[i]->clone());
		else
			nuevos_nodos.push_back(n->nodos[i]);
	this->nodos  = nuevos_nodos;
	this->borrados = n->borrados;
	this->num_nodos = n->num_nodos ;
	this->num_nodos_validos = n->num_nodos_validos;
	this->maxx = n->maxx;
	this->minx = n->minx;
	this->maxy = n->maxy;
	this->miny = n->miny;
	this->maxz = n->maxz;
	this->minz = n->minz;

	nodos_marcados = NULL;
}

Nodos *Nodos::clone() {
	return new Nodos(this);
}

int Nodos::addNodo(Nodo* n) {
    Punto p = n->getPunto();
		    double x = p.getX();
		    double y = p.getY();
		    double z = p.getZ();
		    if(x>maxx) maxx = x;
		    if(x<minx) minx = x;
		    if(y>maxy) maxy = y;
		    if(y<miny) miny = y;
		    if(z>maxz) maxz = z;
		    if(z<minz) minz = z;


    // Si existe un indice en que haya un punto que fue borrado insertamos el punto ahi.
    if(borrados.size() > 0) {
        int ind = borrados[0];
        nodos[ind] = n;
        borrados.erase(borrados.begin());
        num_nodos_validos++; // actualizamos el numero de nodos validos
        return ind;
    }
    else {
        nodos.push_back(n); // agregamos el punto al contenedor.
        num_nodos++; // actualizamos el numero de nodos del contenedor
        num_nodos_validos++; // actualizamos el numero de nodos validos
        return (nodos.size()-1);
    }
}

void Nodos::eraseNodo(int indice) {
    assert((indice < (int)nodos.size()) && (indice >= 0));
    if(nodos[indice] != 0) {
		delete nodos[indice];
        nodos[indice] = 0;
        borrados.push_back(indice);
        num_nodos_validos--;
    }
}

Nodo* Nodos::getNodo(int indice) {
    assert((indice < (int)nodos.size()) && (indice >= 0));
    return nodos[indice];
}

Nodo* Nodos::operator[](int indice) {
    assert((indice < (int)nodos.size()) && (indice >= 0));
    return nodos[indice];
}

double Nodos::get_maxx(){
    return maxx;
}
double Nodos::get_minx(){
    return minx;
}
double Nodos::get_maxy(){
    return maxy;
}
double Nodos::get_miny(){
    return miny;
}
double Nodos::get_maxz(){
    return maxz;
}
double Nodos::get_minz(){
    return minz;
}


void Nodos::moverNodo(int indice, double dist) {
    if(indice == -1) {
        return;
    }
    if(indice >= (int)nodos.size() || indice < 0) {
        cout << "Error: Moviendo Nodo(" << indice << "). Numero de nodos = " << nodos.size() << endl;
        assert((indice < (int)nodos.size()) && (indice >= 0));
    }
    Nodo *n = nodos[indice];
    //movemos el nodo una distancia dist.
    double x,y,z;
    if(n != 0) {
        Vect normal = n->getNormal();
        if(normal.largo() > 0) {
            x=n->getPunto().getX()+normal.getPunto().getX()*dist;
            y=n->getPunto().getY()+normal.getPunto().getY()*dist;
            z=n->getPunto().getZ()+normal.getPunto().getZ()*dist;
            n->setPunto(Punto(x,y,z));
        }
    }
}

void Nodos::moverNodo(int indice, double x, double y, double z, double dist) {
    if(indice == -1) {
        return;
    }
    if(indice >= (int)nodos.size() || indice < 0) {
        cout << "Error: Moviendo Nodo(" << indice << "). Numero de nodos = " << nodos.size() << endl;
        assert((indice < (int)nodos.size()) && (indice >= 0));
    }
    Nodo *n = nodos[indice];
    //movemos el nodo una distancia dist.
    double x1,y1,z1;
    if(n != 0) {
        x1=n->getPunto().getX()+x*dist;
        y1=n->getPunto().getY()+y*dist;
        z1=n->getPunto().getZ()+z*dist;
        n->setPunto(Punto(x1,y1,z1));
    }
};

/*void Nodos::moverNodo(int indice, double x, double y, double z, double dist) {
    moverNodo(indice, x, y, z, dist);
    Nodo *n = nodos[indice];
    if(n != 0){
        double x1=n->getPunto().getX();
        double y1=n->getPunto().getY();

        float getY = (y1-maxy)/(maxy-miny)*0.9 + 0.063;
        n->setTexturePoint(0.3423 + (maxx - x1)/(maxx-minx)*0.3  , getY >0.0f? 0.0f: getY);
    }
};*/

void Nodos::moverNodoSegunConcentracion(int indice, double val) {
    if(indice == -1) {
        return;
    }
    if(indice >= (int)nodos.size() || indice < 0) {
        cout << "Error: Moviendo Nodo(" << indice << "). Numero de nodos = " << nodos.size() << endl;
        assert((indice < (int)nodos.size()) && (indice >= 0));
    }
    Nodo *n = nodos[indice];
    //movemos el nodo una distancia dist.
    double x,y,z;
    if(n != 0) {
        Vect normal = n->getNormal();
        if(normal.largo() > 0) {
            x=n->getPunto().getX()+normal.getPunto().getX()*val*n->getConcentracion();
            y=n->getPunto().getY()+normal.getPunto().getY()*val*n->getConcentracion();
            z=n->getPunto().getZ()+normal.getPunto().getZ()*val*n->getConcentracion();
            n->setPunto(Punto(x,y,z));
        }
    }
}

void Nodos::moverTodosAUV(int indice, double dist){
    switch(indice){
    case 0:
        //# AUV0   Upper lip raiser (AU10)
        moverNodo(6, 0.000000,0.086957,0.021739, dist);
        moverNodo(32, 0.000000, 0.065217, 0.021739, dist);
        moverNodo(57, 0.000000, 0.065217, 0.021739, dist);
        moverNodo(70, 0.000000, 0.050000, 0.021739, dist);
        moverNodo(71, 0.000000, 0.050000, 0.021739, dist);
        moverNodo(72, 0.000000, 0.050000, 0.021739, dist);
        moverNodo(73, 0.000000, 0.050000, 0.021739, dist);
        moverNodo(78, 0.000000, 0.065217, 0.021739, dist);
        moverNodo(79, 0.000000, 0.020000, 0.000000, dist);
        moverNodo(80, 0.000000, 0.020000, 0.000000, dist);
        break;
    case 1:
        //# AUV2   Lip stretcher (AU20)
        moverNodo(30, 0.090000, 0.000000, -0.090000, dist);
        moverNodo(7, 0.000000, 0.032500, -0.017391, dist);
        moverNodo(32, 0.000000, -0.022000, -0.025500, dist);
        moverNodo(6, 0.000000, -0.022000, -0.010000, dist);
        moverNodo(55, -0.090000, 0.000000, -0.090000, dist);
        moverNodo(57, 0.000000, -0.022000, -0.025500, dist);
        moverNodo(70, 0.045000, -0.020000, -0.020000, dist);
        moverNodo(71, -0.045000, -0.020000, -0.020000, dist);
        moverNodo(72, 0.040000, 0.000000, -0.020000, dist);
        moverNodo(73, -0.040000, 0.000000, -0.020000, dist);
        moverNodo(74, 0.040000, 0.000000, -0.020000, dist);
        moverNodo(75, -0.040000, 0.000000, -0.020000, dist);
        moverNodo(76, 0.045000, 0.023000, -0.020000, dist);
        moverNodo(77, -0.045000, 0.023000, -0.020000, dist);
        moverNodo(79, 0.080000, 0.000000, -0.080000, dist);
        moverNodo(80, -0.080000, 0.000000, -0.080000, dist);
        moverNodo(81, 0.040000, 0.000000, -0.040000, dist);
        moverNodo(82, -0.040000, 0.000000, -0.040000, dist);
        break;
    case 2:
        //# AUV3   Brow lowerer (AU4)
        moverNodo(16, -0.130435, -0.130435, 0.000000, dist);
        moverNodo(15, -0.086957, -0.130435, 0.017391, dist);
        moverNodo(17, -0.086957, -0.130435, 0.017391, dist);
        moverNodo(14, 0.000000, -0.065217, 0.000000, dist);
        moverNodo(41, 0.130435, -0.130435, 0.000000, dist);
        moverNodo(40, 0.086957, -0.130435, 0.017391, dist);
        moverNodo(42, 0.086957, -0.130435, 0.017391, dist);
        moverNodo(39, 0.000000, -0.065217, 0.000000, dist);
        moverNodo(20, 0.000000, -0.034783, 0.000000, dist);
        moverNodo(45, 0.000000, -0.034783, 0.000000, dist);
        moverNodo(58, 0.000000, -0.026087, 0.000000, dist);
        moverNodo(60, 0.000000, -0.026087, 0.000000, dist);
        moverNodo(62, 0.000000, -0.026087, 0.000000, dist);
        moverNodo(64, 0.000000, -0.026087, 0.000000, dist);
        break;
    case 3:
    //# AUV5   Outer brow raiser (AU2)
    //8
        moverNodo(14, 0.021739, 0.173913, -0.021739, dist);
        moverNodo(15, 0.000000, 0.152174, -0.021739, dist);
        moverNodo(16, 0.000000, 0.021739, 0.000000, dist);
        moverNodo(17, 0.000000, 0.152174, -0.021739, dist);
        moverNodo(39, -0.021739, 0.173913, -0.021739, dist);
        moverNodo(40, 0.000000, 0.152174, -0.021739, dist);
        moverNodo(41, 0.000000, 0.021739, 0.000000, dist);
        moverNodo(42, 0.000000, 0.152174, -0.021739, dist);
        break;
    case 4:
        //# AUV6   Eyes closed (AU42/43/44/45)
        //12
        moverNodo(20, 0.000000, -0.062000, 0.010000, dist);
        moverNodo(21, 0.000000, 0.020000, 0.010000, dist);
        moverNodo(45, 0.000000, -0.062000, 0.010000, dist);
        moverNodo(46, 0.000000, 0.020000, 0.010000, dist);
        moverNodo(88, 0.000000, -0.045000, 0.007000, dist);
        moverNodo(89, 0.000000, -0.045000, 0.007000, dist);
        moverNodo(90, 0.000000, 0.015000, 0.007000, dist);
        moverNodo(91, 0.000000, 0.015000, 0.007000, dist);
        moverNodo(96, 0.000000, -0.045000, 0.007000, dist);
        moverNodo(97, 0.000000, -0.045000, 0.007000, dist);
        moverNodo(98, 0.000000, 0.015000, 0.007000, dist);
        moverNodo(99, 0.000000, 0.015000, 0.007000, dist);
        break;
    case 5:
    //# AUV7   Lid tightener (AU7)
    //12
        moverNodo(20, 0.000000, -0.056000, 0.010000, dist);
        moverNodo(21, 0.000000, 0.026000, 0.010000, dist);
        moverNodo(45, 0.000000, -0.056000, 0.010000, dist);
        moverNodo(46, 0.000000, 0.026000, 0.010000, dist);
        moverNodo(88, 0.000000, -0.038000, 0.007000, dist);
        moverNodo(89, 0.000000, -0.038000, 0.007000, dist);
        moverNodo(90, 0.000000, 0.022000, 0.007000, dist);
        moverNodo(91, 0.000000, 0.022000, 0.007000, dist);
        moverNodo(96, 0.000000, -0.038000, 0.007000, dist);
        moverNodo(97, 0.000000, -0.038000, 0.007000, dist);
        moverNodo(98, 0.000000, 0.022000, 0.007000, dist);
        moverNodo(99, 0.000000, 0.022000, 0.007000, dist);
        break;
    case 6:
        //# AUV8   Nose wrinkler (AU9)
        //23
        moverNodo(2, 0.000000, -0.086957, 0.013043, dist);
        moverNodo(3, 0.000000, -0.043478, 0.000000, dist);
        moverNodo(4, 0.000000, 0.086957, 0.000000, dist);
        moverNodo(25, 0.000000, 0.043478, -0.017391, dist);
        moverNodo(24, 0.000000, 0.043478, -0.008696, dist);
        moverNodo(23, 0.000000, 0.017391, 0.000000, dist);
        moverNodo(21, 0.000000, 0.017391, 0.000000, dist);
        moverNodo(50, 0.000000, 0.043478, -0.017391, dist);
        moverNodo(49, 0.000000, 0.043478, -0.008696, dist);
        moverNodo(48, 0.000000, 0.017391, 0.000000, dist);
        moverNodo(46, 0.000000, 0.017391, 0.000000, dist);
        moverNodo(59, 0.000000, 0.008696, 0.000000, dist);
        moverNodo(61, 0.000000, 0.008696, 0.000000, dist);
        moverNodo(63, 0.000000, 0.008696, 0.000000, dist);
        moverNodo(65, 0.000000, 0.008696, 0.000000, dist);
        moverNodo(90, 0.000000, 0.017391, 0.000000, dist);
        moverNodo(91, 0.000000, 0.017391, 0.000000, dist);
        moverNodo(92, 0.000000, 0.017391, 0.000000, dist);
        moverNodo(93, 0.000000, 0.017391, 0.000000, dist);
        moverNodo(98, 0.000000, 0.017391, 0.000000, dist);
        moverNodo(99, 0.000000, 0.017391, 0.000000, dist);
        moverNodo(100, 0.000000, 0.017391, 0.000000, dist);
        moverNodo(101, 0.000000, 0.017391, 0.000000, dist);
        break;

    case 7:
         //# AUV9   Lip presser (AU23/24)
        //8
        moverNodo(7, 0.000000, 0.032500, 0.000000, dist);
        moverNodo(32, 0.000000, -0.020000, 0.000000, dist);
        moverNodo(57, 0.000000, -0.020000, 0.000000, dist);
        moverNodo(6, 0.000000, -0.021000, 0.000000, dist);
        moverNodo(70, 0.000000, -0.020000, 0.000000, dist);
        moverNodo(71, 0.000000, -0.020000, 0.000000, dist);
        moverNodo(76, 0.000000, 0.023000, 0.000000, dist);
        moverNodo(77, 0.000000, 0.023000, 0.000000, dist);
        break;
    case 8:
        //# AUV10 Upper lid raiser (AU5)
        //6
        moverNodo(20, 0.000000, 0.030000, -0.010000, dist);
        moverNodo(45, 0.000000, 0.030000, -0.010000, dist);
        moverNodo(88, 0.000000, 0.015000, -0.007000, dist);
        moverNodo(89, 0.000000, 0.015000, -0.007000, dist);
        moverNodo(96, 0.000000, 0.015000, -0.007000, dist);
        moverNodo(97, 0.000000, 0.015000, -0.007000, dist);
        break;
    case 9:
    //# AUV11 Jaw drop (AU26/27)
        moverNodo(34, 0.000000, -0.260000, -0.050000, dist);
        moverNodo(7, 0.000000, -0.260000, -0.050000, dist);
        moverNodo(8, 0.000000, -0.260000, -0.100000, dist);
        moverNodo(9, 0.000000, -0.130000, -0.150000, dist);
        moverNodo(31, 0.000000, -0.150000, -0.130000, dist);
        moverNodo(56, 0.000000, -0.150000, -0.130000, dist);
        moverNodo(74, 0.000000, -0.200000, -0.050000, dist);
        moverNodo(75, 0.000000, -0.200000, -0.050000, dist);
        moverNodo(76, 0.000000, -0.200000, -0.050000, dist);
        moverNodo(77, 0.000000, -0.200000, -0.050000, dist);
        moverNodo(79, 0.000000, -0.020000, 0.000000, dist);
        moverNodo(80, 0.000000, -0.020000, 0.000000, dist);
        break;
    case 10:
        //# AUV14 Lip corner depressor (AU13/15)
        //14
        moverNodo(30, 0.000000, -0.140000, -0.010000, dist);
        moverNodo(55, 0.000000, -0.140000, -0.010000, dist);
        moverNodo(79, 0.000000, -0.100000, -0.008000, dist);
        moverNodo(80, 0.000000, -0.100000, -0.008000, dist);
        moverNodo(70, 0.000000, -0.030000, -0.020000, dist);
        moverNodo(71, 0.000000, -0.030000, -0.020000, dist);
        moverNodo(72, 0.000000, -0.030000, -0.020000, dist);
        moverNodo(73, 0.000000, -0.030000, -0.020000, dist);
        moverNodo(74, 0.000000, -0.030000, -0.020000, dist);
        moverNodo(75, 0.000000, -0.030000, -0.020000, dist);
        moverNodo(76, 0.000000, -0.040000, -0.020000, dist);
        moverNodo(77, 0.000000, -0.040000, -0.020000, dist);
        moverNodo(81, 0.000000, -0.040000, -0.000000, dist);
        moverNodo(82, 0.000000, -0.040000, -0.000000, dist);
        break;
    }

}

Punto *Nodos::movimientoAUV(int number_nodo, int indice_unit){
    int nodo = -1;
    return new Punto(0,0.0,0);
    for(int i = 0; i< n_marcados;++i){
        if(number_nodo == nodos_marcados[i]){
            nodo = i;
            break;
        }
    }

    switch(indice_unit){
    case 0:
        if(nodo == 6) return new Punto(0.000000,0.086957,0.02173);
        if(nodo == 32) return new Punto(0.000000, 0.065217, 0.02173);
        if(nodo == 57) return new Punto(0.000000, 0.065217, 0.02173);
        if(nodo == 70) return new Punto(0.000000, 0.050000, 0.02173);
        if(nodo == 71) return new Punto(0.000000, 0.050000, 0.02173);
        if(nodo == 72) return new Punto(0.000000, 0.050000, 0.02173);
        if(nodo == 73) return new Punto(0.000000, 0.050000, 0.02173);
        if(nodo == 78) return new Punto(0.000000, 0.065217, 0.02173);
        if(nodo == 79) return new Punto(0.000000, 0.020000, 0.00000);
        if(nodo == 80) return new Punto(0.000000, 0.020000, 0.00000);
        break;
    case 1:
        if(nodo == 30) return new Punto(0.090000, 0.000000, -0.09000);
        if(nodo == 7) return new Punto(0.000000, 0.032500, -0.01739);
        if(nodo == 32) return new Punto(0.000000, -0.022000, -0.02550);
        if(nodo == 6) return new Punto(0.000000, -0.022000, -0.01000);
        if(nodo == 55) return new Punto(-0.090000, 0.000000, -0.09000);
        if(nodo == 57) return new Punto(0.000000, -0.022000, -0.02550);
        if(nodo == 70) return new Punto(0.045000, -0.020000, -0.02000);
        if(nodo == 71) return new Punto(-0.045000, -0.020000, -0.02000);
        if(nodo == 72) return new Punto(0.040000, 0.000000, -0.02000);
        if(nodo == 73) return new Punto(-0.040000, 0.000000, -0.02000);
        if(nodo == 74) return new Punto(0.040000, 0.000000, -0.02000);
        if(nodo == 75) return new Punto(-0.040000, 0.000000, -0.02000);
        if(nodo == 76) return new Punto(0.045000, 0.023000, -0.02000);
        if(nodo == 77) return new Punto(-0.045000, 0.023000, -0.02000);
        if(nodo == 79) return new Punto(0.080000, 0.000000, -0.08000);
        if(nodo == 80) return new Punto(-0.080000, 0.000000, -0.08000);
        if(nodo == 81) return new Punto(0.040000, 0.000000, -0.04000);
        if(nodo == 82) return new Punto(-0.040000, 0.000000, -0.04000);
        break;
    case 2:
        if(nodo == 16) return new Punto(-0.130435, -0.130435, 0.00000);
        if(nodo == 15) return new Punto(-0.086957, -0.130435, 0.01739);
        if(nodo == 17) return new Punto(-0.086957, -0.130435, 0.01739);
        if(nodo == 14) return new Punto(0.000000, -0.065217, 0.00000);
        if(nodo == 41) return new Punto(0.130435, -0.130435, 0.00000);
        if(nodo == 40) return new Punto(0.086957, -0.130435, 0.01739);
        if(nodo == 42) return new Punto(0.086957, -0.130435, 0.01739);
        if(nodo == 39) return new Punto(0.000000, -0.065217, 0.00000);
        if(nodo == 20) return new Punto(0.000000, -0.034783, 0.00000);
        if(nodo == 45) return new Punto(0.000000, -0.034783, 0.00000);
        if(nodo == 58) return new Punto(0.000000, -0.026087, 0.00000);
        if(nodo == 60) return new Punto(0.000000, -0.026087, 0.00000);
        if(nodo == 62) return new Punto(0.000000, -0.026087, 0.00000);
        if(nodo == 64) return new Punto(0.000000, -0.026087, 0.00000);
        break;
    case 3:
        if(nodo == 14) return new Punto(0.021739, 0.173913, -0.02173);
        if(nodo == 15) return new Punto(0.000000, 0.152174, -0.02173);
        if(nodo == 16) return new Punto(0.000000, 0.021739, 0.00000);
        if(nodo == 17) return new Punto(0.000000, 0.152174, -0.02173);
        if(nodo == 39) return new Punto(-0.021739, 0.173913, -0.02173);
        if(nodo == 40) return new Punto(0.000000, 0.152174, -0.02173);
        if(nodo == 41) return new Punto(0.000000, 0.021739, 0.00000);
        if(nodo == 42) return new Punto(0.000000, 0.152174, -0.02173);
        break;
    case 4:
        if(nodo == 20) return new Punto(0.000000, -0.062000, 0.01000);
        if(nodo == 21) return new Punto(0.000000, 0.020000, 0.01000);
        if(nodo == 45) return new Punto(0.000000, -0.062000, 0.01000);
        if(nodo == 46) return new Punto(0.000000, 0.020000, 0.01000);
        if(nodo == 88) return new Punto(0.000000, -0.045000, 0.00700);
        if(nodo == 89) return new Punto(0.000000, -0.045000, 0.00700);
        if(nodo == 90) return new Punto(0.000000, 0.015000, 0.00700);
        if(nodo == 91) return new Punto(0.000000, 0.015000, 0.00700);
        if(nodo == 96) return new Punto(0.000000, -0.045000, 0.00700);
        if(nodo == 97) return new Punto(0.000000, -0.045000, 0.00700);
        if(nodo == 98) return new Punto(0.000000, 0.015000, 0.00700);
        if(nodo == 99) return new Punto(0.000000, 0.015000, 0.00700);
        break;
    case 5:
        if(nodo == 20) return new Punto(0.000000, -0.056000, 0.01000);
        if(nodo == 21) return new Punto(0.000000, 0.026000, 0.01000);
        if(nodo == 45) return new Punto(0.000000, -0.056000, 0.01000);
        if(nodo == 46) return new Punto(0.000000, 0.026000, 0.01000);
        if(nodo == 88) return new Punto(0.000000, -0.038000, 0.00700);
        if(nodo == 89) return new Punto(0.000000, -0.038000, 0.00700);
        if(nodo == 90) return new Punto(0.000000, 0.022000, 0.00700);
        if(nodo == 91) return new Punto(0.000000, 0.022000, 0.00700);
        if(nodo == 96) return new Punto(0.000000, -0.038000, 0.00700);
        if(nodo == 97) return new Punto(0.000000, -0.038000, 0.00700);
        if(nodo == 98) return new Punto(0.000000, 0.022000, 0.00700);
        if(nodo == 99) return new Punto(0.000000, 0.022000, 0.00700);
        break;
    case 6:
        if(nodo == 2) return new Punto(0.000000, -0.086957, 0.01304);
        if(nodo == 3) return new Punto(0.000000, -0.043478, 0.00000);
        if(nodo == 4) return new Punto(0.000000, 0.086957, 0.00000);
        if(nodo == 25) return new Punto(0.000000, 0.043478, -0.01739);
        if(nodo == 24) return new Punto(0.000000, 0.043478, -0.00869);
        if(nodo == 23) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 21) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 50) return new Punto(0.000000, 0.043478, -0.01739);
        if(nodo == 49) return new Punto(0.000000, 0.043478, -0.00869);
        if(nodo == 48) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 46) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 59) return new Punto(0.000000, 0.008696, 0.00000);
        if(nodo == 61) return new Punto(0.000000, 0.008696, 0.00000);
        if(nodo == 63) return new Punto(0.000000, 0.008696, 0.00000);
        if(nodo == 65) return new Punto(0.000000, 0.008696, 0.00000);
        if(nodo == 90) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 91) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 92) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 93) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 98) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 99) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 100) return new Punto(0.000000, 0.017391, 0.00000);
        if(nodo == 101) return new Punto(0.000000, 0.017391, 0.00000);
        break;
    case 7:
        if(nodo == 7) return new Punto(0.000000, 0.032500, 0.00000);
        if(nodo == 32) return new Punto(0.000000, -0.020000, 0.00000);
        if(nodo == 57) return new Punto(0.000000, -0.020000, 0.00000);
        if(nodo == 6) return new Punto(0.000000, -0.021000, 0.00000);
        if(nodo == 70) return new Punto(0.000000, -0.020000, 0.00000);
        if(nodo == 71) return new Punto(0.000000, -0.020000, 0.00000);
        if(nodo == 76) return new Punto(0.000000, 0.023000, 0.00000);
        if(nodo == 77) return new Punto(0.000000, 0.023000, 0.00000);
        break;
    case 8:
        if(nodo == 20) return new Punto(0.000000, 0.030000, -0.01000);
        if(nodo == 45) return new Punto(0.000000, 0.030000, -0.01000);
        if(nodo == 88) return new Punto(0.000000, 0.015000, -0.00700);
        if(nodo == 89) return new Punto(0.000000, 0.015000, -0.00700);
        if(nodo == 96) return new Punto(0.000000, 0.015000, -0.00700);
        if(nodo == 97) return new Punto(0.000000, 0.015000, -0.00700);
        break;
    case 9:
        if(nodo == 34) return new Punto(0.000000, -0.260000, -0.05000);
        if(nodo == 7) return new Punto(0.000000, -0.260000, -0.05000);
        if(nodo == 8) return new Punto(0.000000, -0.260000, -0.10000);
        if(nodo == 9) return new Punto(0.000000, -0.130000, -0.15000);
        if(nodo == 31) return new Punto(0.000000, -0.150000, -0.13000);
        if(nodo == 56) return new Punto(0.000000, -0.150000, -0.13000);
        if(nodo == 74) return new Punto(0.000000, -0.200000, -0.05000);
        if(nodo == 75) return new Punto(0.000000, -0.200000, -0.05000);
        if(nodo == 76) return new Punto(0.000000, -0.200000, -0.05000);
        if(nodo == 77) return new Punto(0.000000, -0.200000, -0.05000);
        if(nodo == 79) return new Punto(0.000000, -0.020000, 0.00000);
        if(nodo == 80) return new Punto(0.000000, -0.020000, 0.00000);
        break;
    case 10:
        if(nodo == 30) return new Punto(0.000000, -0.140000, -0.01000);
        if(nodo == 55) return new Punto(0.000000, -0.140000, -0.01000);
        if(nodo == 79) return new Punto(0.000000, -0.100000, -0.00800);
        if(nodo == 80) return new Punto(0.000000, -0.100000, -0.00800);
        if(nodo == 70) return new Punto(0.000000, -0.030000, -0.02000);
        if(nodo == 71) return new Punto(0.000000, -0.030000, -0.02000);
        if(nodo == 72) return new Punto(0.000000, -0.030000, -0.02000);
        if(nodo == 73) return new Punto(0.000000, -0.030000, -0.02000);
        if(nodo == 74) return new Punto(0.000000, -0.030000, -0.02000);
        if(nodo == 75) return new Punto(0.000000, -0.030000, -0.02000);
        if(nodo == 76) return new Punto(0.000000, -0.040000, -0.02000);
        if(nodo == 77) return new Punto(0.000000, -0.040000, -0.02000);
        if(nodo == 81) return new Punto(0.000000, -0.040000, -0.00000);
        if(nodo == 82) return new Punto(0.000000, -0.040000, -0.00000);
        break;
    }
    return new Punto(0,0,0);

}

void Nodos::asignar_nodos_marcados(int *clos, int n){
    n_marcados = n;
    nodos_marcados = new int[n];
    for(int i = 0; i < n; ++i){
            nodos_marcados[i] = clos[i];
    }
}

void Nodos::moverShapeUnit(int indice, double dist){
    switch(indice){
        //# Head height
        case 0:
            moverNodo(0, 0.000000, 0.200000, 0.000000, dist);
            moverNodo(1, 0.000000, 0.200000, 0.000000, dist);
            moverNodo(10, 0.000000, 0.200000, 0.000000, dist);
            moverNodo(11, 0.000000, 0.200000, 0.000000, dist);
            moverNodo(12, 0.000000, 0.200000, 0.000000, dist);
            moverNodo(13, 0.000000, 0.200000, 0.000000, dist);
            moverNodo(33, 0.000000, 0.200000, 0.000000, dist);
            moverNodo(35, 0.000000, 0.200000, 0.000000, dist);
            moverNodo(36, 0.000000, 0.200000, 0.000000, dist);
            moverNodo(37, 0.000000, 0.200000, 0.000000, dist);
            moverNodo(38, 0.000000, 0.200000, 0.000000, dist);
            moverNodo(9, 0.000000, -0.200000, 0.000000, dist);
            moverNodo(29, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(54, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(31, 0.000000, -0.200000, 0.000000, dist);
            moverNodo(56, 0.000000, -0.200000, 0.000000, dist);
            break;
        //# Eyebrows vertical position
        case 1:
            moverNodo(14, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(15, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(16, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(17, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(39, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(40, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(41, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(42, 0.000000, 0.100000, 0.000000, dist);
            break;
        //# Eyes vertical position
        case 2:
            moverNodo(18, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(19, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(20, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(21, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(22, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(23, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(43, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(44, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(45, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(46, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(47, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(48, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(58, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(59, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(60, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(61, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(62, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(63, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(64, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(65, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(86, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(87, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(88, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(89, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(90, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(91, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(92, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(93, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(94, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(95, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(96, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(97, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(98, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(99, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(100, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(101, 0.000000, 0.100000, 0.000000, dist);
            break;
        //# Eyes, width
        case 3:
            moverNodo(19, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(86, 0.050000, 0.000000, 0.000000, dist);
            moverNodo(88, 0.050000, 0.000000, 0.000000, dist);
            moverNodo(90, 0.050000, 0.000000, 0.000000, dist);
            moverNodo(92, 0.050000, 0.000000, 0.000000, dist);
            moverNodo(94, -0.050000, 0.000000, 0.000000, dist);
            moverNodo(96, -0.050000, 0.000000, 0.000000, dist);
            moverNodo(98, -0.050000, 0.000000, 0.000000, dist);
            moverNodo(100, -0.050000, 0.000000, 0.000000, dist);
            moverNodo(22, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(44, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(87, -0.050000, 0.000000, 0.000000, dist);
            moverNodo(89, -0.050000, 0.000000, 0.000000, dist);
            moverNodo(91, -0.050000, 0.000000, 0.000000, dist);
            moverNodo(93, -0.050000, 0.000000, 0.000000, dist);
            moverNodo(95, 0.050000, 0.000000, 0.000000, dist);
            moverNodo(97, 0.050000, 0.000000, 0.000000, dist);
            moverNodo(99, 0.050000, 0.000000, 0.000000, dist);
            moverNodo(101, 0.050000, 0.000000, 0.000000, dist);
            moverNodo(47, 0.100000, 0.000000, 0.000000, dist);
            break;
        //# Eyes, height
        case 4:
            moverNodo(18, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(20, 0.000000, 0.050000, 0.000000, dist);
            moverNodo(21, 0.000000, -0.050000, 0.000000, dist);
            moverNodo(23, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(43, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(45, 0.000000, 0.050000, 0.000000, dist);
            moverNodo(46, 0.000000, -0.050000, 0.000000, dist);
            moverNodo(48, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(86, 0.000000, 0.070000, 0.000000, dist);
            moverNodo(87, 0.000000, 0.070000, 0.000000, dist);
            moverNodo(94, 0.000000, 0.070000, 0.000000, dist);
            moverNodo(95, 0.000000, 0.070000, 0.000000, dist);
            moverNodo(92, 0.000000, -0.070000, 0.000000, dist);
            moverNodo(93, 0.000000, -0.070000, 0.000000, dist);
            moverNodo(100, 0.000000, -0.070000, 0.000000, dist);
            moverNodo(101, 0.000000, -0.070000, 0.000000, dist);
            moverNodo(88, 0.000000, 0.035000, 0.000000, dist);
            moverNodo(89, 0.000000, 0.035000, 0.000000, dist);
            moverNodo(96, 0.000000, 0.035000, 0.000000, dist);
            moverNodo(97, 0.000000, 0.035000, 0.000000, dist);
            moverNodo(90, 0.000000, -0.035000, 0.000000, dist);
            moverNodo(91, 0.000000, -0.035000, 0.000000, dist);
            moverNodo(98, 0.000000, -0.035000, 0.000000, dist);
            moverNodo(99, 0.000000, -0.035000, 0.000000, dist);
            break;
        //# Eye separation distance
        case 5:
            moverNodo(18, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(19, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(20, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(21, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(22, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(23, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(43, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(44, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(45, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(46, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(47, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(48, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(58, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(59, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(60, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(61, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(62, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(63, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(64, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(65, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(86, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(87, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(88, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(89, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(90, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(91, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(92, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(93, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(94, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(95, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(96, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(97, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(98, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(99, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(100, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(101, -0.100000, 0.000000, 0.000000, dist);
            break;
        //# Cheeks z
        case 6:
            moverNodo(26, 0.000000, 0.000000, 0.100000, dist);
            moverNodo(51, 0.000000, 0.000000, 0.100000, dist);
            break;
        //# Nose z-extension
        case 7:
            moverNodo(4, 0.000000, 0.000000, 0.100000, dist);
            moverNodo(66, 0.000000, 0.000000, 0.070000, dist);
            moverNodo(67, 0.000000, 0.000000, 0.070000, dist);
            moverNodo(83, 0.000000, 0.000000, 0.050000, dist);
            moverNodo(84, 0.000000, 0.000000, 0.050000, dist);
            moverNodo(85, 0.000000, 0.000000, 0.050000, dist);
            break;
        //# Nose vertical position
        case 8:
            moverNodo(3, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(4, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(4, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(5, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(24, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(25, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(49, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(50, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(66, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(67, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(68, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(69, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(83, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(84, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(85, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(102, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(103, 0.000000, 0.100000, 0.000000, dist);
            break;
        //# Nose, pointing up
        case 9:
            moverNodo(4, 0.000000, 0.050000, 0.000000, dist);
            moverNodo(66, 0.000000, 0.050000, 0.000000, dist);
            moverNodo(67, 0.000000, 0.050000, 0.000000, dist);
            break;
        //# Mouth vertical position
        case 10:
            moverNodo(6, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(7, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(8, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(30, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(32, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(34, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(55, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(57, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(70, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(71, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(72, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(73, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(74, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(75, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(76, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(77, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(78, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(79, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(80, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(81, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(82, 0.000000, 0.100000, 0.000000, dist);
            break;
        //# Mouth width
        case 11:
            moverNodo(30, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(55, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(79, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(80, -0.100000, 0.000000, 0.000000, dist);
            moverNodo(70, 0.050000, 0.000000, 0.000000, dist);
            moverNodo(71, -0.050000, 0.000000, 0.000000, dist);
            moverNodo(72, 0.050000, 0.000000, 0.000000, dist);
            moverNodo(73, -0.050000, 0.000000, 0.000000, dist);
            moverNodo(74, 0.050000, 0.000000, 0.000000, dist);
            moverNodo(75, -0.050000, 0.000000, 0.000000, dist);
            moverNodo(76, 0.050000, 0.000000, 0.000000, dist);
            moverNodo(77, -0.050000, 0.000000, 0.000000, dist);
            moverNodo(81, 0.050000, 0.000000, 0.000000, dist);
            moverNodo(82, -0.050000, 0.000000, 0.000000, dist);
            break;
        //# Eyes vertical difference
        case 12:
            moverNodo(18, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(19, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(20, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(21, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(22, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(23, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(43, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(44, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(45, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(46, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(47, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(48, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(58, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(59, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(60, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(61, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(62, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(63, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(64, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(65, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(86, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(87, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(88, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(89, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(90, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(91, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(92, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(93, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(94, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(95, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(96, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(97, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(98, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(99, 0.000000, 0.100000, 0.000000, dist);
            moverNodo(100, 0.000000, -0.100000, 0.000000, dist);
            moverNodo(101, 0.000000, 0.100000, 0.000000, dist);
            break;
        //# Chin width
        case 13:
            moverNodo(29, 0.100000, 0.000000, 0.000000, dist);
            moverNodo(54, -0.100000, 0.000000, 0.000000, dist);
            break;
    }
}


void Nodos::regresarNodo(int indice, double dist) {
    if(indice == -1) {
        return;
    }
    if(indice >= (int)nodos.size() || indice < 0) {
        cout << "Error: Regresando Nodo(" << indice << "). Numero de nodos = " << nodos.size() << endl;
        assert((indice < (int)nodos.size()) && (indice >= 0));
    }
    Nodo *n = nodos[indice];
    //regresamos el nodo una distancia dist.
    double x,y,z;
    if(n != 0) {
        Vect normal = n->getNormal();
        if(normal.largo() > 0) {
            x=n->getPunto().getX()-normal.getPunto().getX()*dist;
            y=n->getPunto().getY()-normal.getPunto().getY()*dist;
            z=n->getPunto().getZ()-normal.getPunto().getZ()*dist;
            n->setPunto(Punto(x,y,z));
        }
    }
}

void Nodos::regresarNodoSegunConcentracion(int indice, double val) {
    if(indice == -1) {
        return;
    }
    if(indice >= (int)nodos.size() || indice < 0) {
        cout << "Error: Regresando Nodo(" << indice << "). Numero de nodos = " << nodos.size() << endl;
        assert((indice < (int)nodos.size()) && (indice >= 0));
    }
    Nodo *n = nodos[indice];
    //regresamos el nodo una distancia dist.
    double x,y,z;
    if(n != 0) {
        Vect normal = n->getNormal();
        if(normal.largo() > 0) {
            x=n->getPunto().getX()-normal.getPunto().getX()*val*n->getConcentracion();
            y=n->getPunto().getY()-normal.getPunto().getY()*val*n->getConcentracion();
            z=n->getPunto().getZ()-normal.getPunto().getZ()*val*n->getConcentracion();
            n->setPunto(Punto(x,y,z));
        }
    }
}

void Nodos::moverTodos(double dist) {
    for(int i=0; i<(int)nodos.size(); i++) {
        if(nodos[i] != 0) {
            moverNodo(i,dist);
        }
    }
}

void Nodos::moverTodosSegunConcentracion(double val) {
    for(int i=0; i<(int)nodos.size(); i++) {
        if(nodos[i] != 0) {
            moverNodo(i,val*nodos[i]->getConcentracion());
        }
    }
}

int Nodos::getNumNodos() {
    assert(num_nodos == (int)nodos.size()); // nos aseguramos que sean iguales
    return num_nodos;
}

int Nodos::getNumNodosValidos() {
    assert(num_nodos_validos == (int)nodos.size() - (int)borrados.size()); // nos aseguramos que sean iguales
    return num_nodos_validos;
}

void Nodos::addCaraNodo(int indice, int cara) {
    assert((indice < (int)nodos.size()) && (indice >= 0));
    nodos[indice]->addCara(cara);
}

void Nodos::addArcoNodo(int indice, int arco) {

    if((indice >= (int)nodos.size()) || (indice < 0)) {
        cout << "indice = " << indice << endl;
        cout << "nodos.size() = " << nodos.size() << endl;
        assert((indice < (int)nodos.size()) && (indice >= 0));
    }
    nodos[indice]->addArco(arco);
}

int Nodos::popNodoVacio(int indice) {
    assert((indice < (int)nodos.size()) && (indice >= 0));
    assert(nodos[indice] == 0);

    int ind_ultimo_nodo = num_nodos-1;
    // borramos los indices vacios que esten al final hascta llegar a un nodo no vacio
    while(nodos[ind_ultimo_nodo] == 0) {
        nodos.erase(nodos.begin()+ind_ultimo_nodo);
        ind_ultimo_nodo--;
    }
    nodos[indice] = nodos[ind_ultimo_nodo];
    nodos.erase(nodos.begin()+ind_ultimo_nodo);
    num_nodos = nodos.size();
    // el numero de nodos validos se mantiene

    //eliminados de borrados el indice
    for(int i=0; i<(int)borrados.size(); i++) {
        if(borrados[i] == indice) {
            borrados.erase(borrados.begin()+i);
        }
    }
    return ind_ultimo_nodo;
}

ostream& operator<<(ostream &os, Nodos *n) {
    os << "Nodos:" << endl;
    os << "  nodos:" << endl;
    for(int i = 0; i < (int)n->nodos.size(); ++i)
    	if(n->nodos[i] == 0)
	    	os << "   " << i << " NULL" << endl;
		else
	    	os << "   " << i << " " << n->nodos[i] << endl;
    os << "  borrados:" << endl;
    for(int i = 0; i < (int)n->borrados.size(); ++i)
    	os << "   " << i << " " << n->borrados[i] << endl;
	os << "  num_nodos: " << n->num_nodos << endl;
	os << "  num_nodos_validos: " << n->num_nodos_validos << endl;
    return os;
}

Nodos::~Nodos(){
	for (int i=0; i<(int)nodos.size(); i++)
		delete nodos[i];
	if(nodos_marcados != NULL)
        delete[] nodos_marcados;
}
