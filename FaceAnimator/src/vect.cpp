#include "vect.h"

Vect::Vect() {
    p = Punto(0,0,0);
}

Vect::Vect(Punto p) {
    this->p = p;
}

Vect::Vect(double x, double y, double z) {
    this->p = Punto(x,y,z);
}

void Vect::setPunto(Punto p) {
    this->p = p;
}

Punto Vect::getPunto() {
    assert(this != 0);
    return this->p;
}

bool Vect::inOrigen() {
    assert(this != 0);
    if(p.getX() == 0 && p.getY() == 0 && p.getZ() == 0) {
        return true;
    }
    return false;
}

double Vect::largo() {
    return sqrt(p.getX()*p.getX()+p.getY()*p.getY()+p.getZ()*p.getZ());
}

double Vect::getAngulo(Vect v) {
    assert(!this->inOrigen() && !v.inOrigen());
	double cos_angulo = (this->prodPunto(v)) / (this->largo() * v.largo());
    if(cos_angulo > 1 && cos_angulo < 1.000001) {
        return 0;
    }
    return acos(cos_angulo);
}

double Vect::prodPunto(Vect v) {
    return p.getX()*v.getPunto().getX()+p.getY()*v.getPunto().getY()+p.getZ()*v.getPunto().getZ();
    }

Vect Vect::prodCruz(Vect v) {
    return Vect(p.getY()*v.getPunto().getZ()-p.getZ()*v.getPunto().getY(),p.getZ()*v.getPunto().getX()-p.getX()*v.getPunto().getZ(),p.getX()*v.getPunto().getY()-p.getY()*v.getPunto().getX());
}

Vect Vect::operator*(double x) {
    assert(this != 0);
    Vect vct = Vect(p.getX()*x,p.getY()*x,p.getZ()*x);
    return vct;
}

Vect Vect::operator+(Vect v) {
    return Vect(p.getX()+v.getPunto().getX(),p.getY()+v.getPunto().getY(),p.getZ()+v.getPunto().getZ());
    }

Vect Vect::operator-(Vect v) {
    return Vect(p.getX()-v.getPunto().getX(),p.getY()-v.getPunto().getY(),p.getZ()-v.getPunto().getZ());
    }

bool Vect::operator==(Vect v) {
    return this->p == v.p;
}

bool Vect::operator!=(Vect v) {
    return this->p != v.p;
}

void  Vect::normalizar(){
    assert(!this->inOrigen());
    double multiplicador=1/this->largo();
    p.setX(multiplicador*p.getX());
    p.setY(multiplicador*p.getY());
    p.setZ(multiplicador*p.getZ());
    }

ostream& operator<<(ostream &os, Vect v){
    os << "Vect(" << v.p.getX() << "," << v.p.getY() << "," << v.p.getZ() << ")";
    return os;
    }

Vect Vect::proyectadoEn(Vect v1, Vect v2, Vect v3){

    Vect norm = (v2-v1).prodCruz(v3-v1);
    double A = norm.getPunto().getX();
    double B = norm.getPunto().getY();
    double C = norm.getPunto().getZ();
    double D = norm.prodPunto(v1);
    double den = A*A + B*B + C*C;

    Punto p = this->getPunto();
    //Vect v(p);
    double t0 = - (A*p.getX() + B*p.getY() + C*p.getZ() - D)/den;
    double x0 = p.getX() + A*t0;
    double y0 = p.getY() + B*t0;
    double z0 = p.getZ() + C*t0;


    return Vect(Punto(x0,y0,z0));

}

bool Vect::estaEnTriangulo(Vect v1, Vect v2, Vect v3){
    bool isIn = true;
    Vect pc1 = (v3-v2).prodCruz(*this-v2);
    Vect pc2 = (v3-v2).prodCruz(v1-v2);
    if (pc1.prodPunto(pc2) < 0) isIn = false;
    if(!isIn) return false;

    pc1 = (v3-v1).prodCruz(*this-v1);
    pc2 = (v3-v1).prodCruz(v2-v1);
    if (pc1.prodPunto(pc2) < 0) isIn = false;
    if(!isIn) return false;

    pc1 = (v1-v3).prodCruz(*this-v3);
    pc2 = (v1-v3).prodCruz(v2-v3);
    if (pc1.prodPunto(pc2) < 0) isIn = false;

    return isIn;
}

Vect::~Vect(){

	}
