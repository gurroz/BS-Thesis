#ifndef POLINOMIO_H
#define POLINOMIO_H

#include <vector>
#include <iostream>
#include <cassert>
#include <math.h>
#include <gsl/gsl_poly.h>

using namespace std;

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
Esta clase representa un polinomio, posee un conjunto de coeficientes y su grado.
 */
class Polinomio{
    private:
        vector<double> coef; // lista de coeficientes del polinomio
        int grado; // grado del polinomio
    public:
        // constructores:
        Polinomio(vector<double> cfs);
        Polinomio(int grado);
        Polinomio(double b, double a); // ax + b

        vector<double> getCoeficientes();
        int getGrado();
        void setCoeficiente(int ind, double valor);
        double operator[](int indice);
        Polinomio* operator+(Polinomio *p); // suma los 2 polinomios.
        Polinomio* operator-(Polinomio *p); // resta los 2 polinomios.
        Polinomio* operator*(Polinomio *p); // multiplica los 2 polinomios.
        int getRaicesCubicas(double &x1, double &x2, double &x3); // setea en los parámetros ingresados por referencia, las raices REALES (1 o 3), de un polinomio cúbico. Retorna el número de raíces REALES encontradas.
        int getRaicesCuadradas(double &x1, double &x2); // setea en los parámetros ingresados por referencia, las raíces REALES (0 o 2), de un polinomio cuadrático. Retorna el número de raíces REALES encontradas.
        int getRaizLineal(double &x1); // setea en el parámetro ingresado por referencia, la raiz del polinomio lineal. Retorna siempre 1.
        double eval(double val); // evalúa el polinomio en ese val y retorna el resultado.
        void imprimir(); // imprime los coeficientes del polinomio.
};

#endif
