#include "polinomio.h"

Polinomio::Polinomio(vector<double> cfs) {
    grado = cfs.size()-1;
    coef = cfs;
}

Polinomio::Polinomio(int grado) {
    this->grado = grado;
    vector<double> coeficientes;
    for(int i=0; i<=grado; i++) {
        coeficientes.push_back(0);
    }
    coeficientes[grado] = 1;
    coef = coeficientes;
}

Polinomio::Polinomio(double b, double a) {
    this->grado = 1;
    coef.push_back(b);
    coef.push_back(a);
}

vector<double> Polinomio::getCoeficientes() {
    return coef;
}

int Polinomio::getGrado() {
    return grado;
}

void Polinomio::setCoeficiente(int ind, double valor) {
    assert(this != 0 && ind>=0);
    if(ind <= this->getGrado()) {
        coef[ind] = valor;
    }
    else {
        for(int i=this->getGrado(); i<ind; i++) {
            coef.push_back(0);
        }
        coef[ind] = valor;
        grado = ind;
    }
}

double Polinomio::operator[](int indice) {
    assert(this != 0 && indice>=0);
    if(indice >= (int)coef.size()) {
        return 0;
    }
    return coef[indice];
}

Polinomio* Polinomio::operator+(Polinomio *p) {
    vector<double> coeficientes;
    for(int i=0; i<(int)coef.size(); i++) {
        coeficientes.push_back((*this)[i] + (*p)[i]);
    }
    if(p->getGrado() > this->getGrado()) {
        for(int i=this->getGrado(); i<p->getGrado(); i++) {
            coeficientes.push_back((*p)[i+1]);
        }
    }
    return new Polinomio(coeficientes);
}

Polinomio* Polinomio::operator-(Polinomio *p) {
    vector<double> coeficientes;
    for(int i=0; i<(int)coef.size(); i++) {
        coeficientes.push_back((*this)[i] - (*p)[i]);
    }
    if(p->getGrado() > this->getGrado()) {
        for(int i=this->getGrado(); i<p->getGrado(); i++) {
            coeficientes.push_back(-(*p)[i+1]);
        }
    }
    return new Polinomio(coeficientes);
}

Polinomio* Polinomio::operator*(Polinomio *p) {
    Polinomio *mult = new Polinomio(this->getGrado()+p->getGrado());
    mult->setCoeficiente(this->getGrado()+p->getGrado(),0);
    for(int i=0; i<=this->getGrado(); i++) {
        for(int j=0; j<=p->getGrado(); j++) {
            mult->setCoeficiente(i+j,(*mult)[i+j] + ((*this)[i] * (*p)[j]) );
        }
    }
    return mult;
}

int Polinomio::getRaicesCubicas(double &x1, double &x2, double &x3) {
    // Nos aseguramos que efectivamente sea un polinomio cúbico.
    assert(this != 0 && this->getGrado()>=3 && (*this)[3] != 0);
    if(this->getGrado() > 3) {
        for(int i=4; i<=this->getGrado(); i++) {
            assert((*this)[i] == 0);
        }
    }
    
    if((*this)[3] != 1.0) {
        double div = (*this)[3];
        this->setCoeficiente(0,(*this)[0]/div);
        this->setCoeficiente(1,(*this)[1]/div);
        this->setCoeficiente(2,(*this)[2]/div);
        this->setCoeficiente(3,(*this)[3]/div);
    }
    int num = gsl_poly_solve_cubic((*this)[2],(*this)[1],(*this)[0],&x1,&x2,&x3);
    return num;
}

int Polinomio::getRaicesCuadradas(double &x1, double &x2) {
    // Nos aseguramos que efectivamente sea un polinomio cuadrático.
    assert(this != 0 && this->getGrado()>=2 && (*this)[2] != 0);
    if(this->getGrado() > 2) {
        for(int i=3; i<=this->getGrado(); i++) {
            assert((*this)[i] == 0);
        }
    }
    int num = gsl_poly_solve_quadratic((*this)[2],(*this)[1],(*this)[0],&x1,&x2);
    return num;
}

int Polinomio::getRaizLineal(double &x1) {
    // Nos aseguramos que efectivamente sea un polinomio lineal.
    assert(this != 0 && this->getGrado()>=1 && (*this)[1] != 0);
    if(this->getGrado() > 1) {
        for(int i=2; i<=this->getGrado(); i++) {
            assert((*this)[i] == 0);
        }
    }
    x1 = -(*this)[0] / (*this)[1];
    return 1;
}

double Polinomio::eval(double val) {
    assert(this != 0);
    double res = 0;
    for(int i=0; i<(int)coef.size(); i++) {
        res = res + coef[i] * pow(val,i);
    }
    return res;
}

void Polinomio::imprimir() {
    if(this != 0) {
        cout << "Polinomio(";
        for(int i=0; i<(int)coef.size(); i++) {
            if(i==0) {
                cout << (*this)[i];
            }
            else {
                cout << " + " << (*this)[i] << "X^" << i << "";
            }
        }
        cout << ")" << endl;
    }
    else {
        cout << "Polinomio nulo" << endl;
    }
}
