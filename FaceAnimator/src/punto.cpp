#include "punto.h"

Punto::Punto() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Punto::Punto(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Punto::setX(double x) {
    this->x = x;
}

void Punto::setY(double y) {
    this->y = y;
}

void Punto::setZ(double z) {
    this->z = z;
}

double Punto::getX() {
    return x;
}

double Punto::getY() {
    return y;
}

double Punto::getZ() {
    return z;
}

double Punto::operator[](int indice) {
    assert(indice == 0 || indice == 1 || indice == 2);
    if(indice == 0) {
        return x;
    }
    else if(indice == 1) {
        return y;
    }
    else if(indice == 2) {
        return z;
    }
    else {
        return 0;
    }
}

bool Punto::operator==(Punto p) {
    return this->x == p.x && this->y == p.y && this->z == p.z;
}

bool Punto::operator!=(Punto p) {
    return !(*this == p);
}

ostream& operator<<(ostream &os, Punto p) {
    os << "Punto(" << p.x << "," << p.y << "," << p.z << ")";
    return os;
}
