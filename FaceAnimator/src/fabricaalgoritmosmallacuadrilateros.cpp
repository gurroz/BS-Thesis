#include "fabricaalgoritmosmallacuadrilateros.h"
#include "algdesplazamientomallacuadrilateros.h"
#include "noverificacion.h"
#include "verificacionnodosvecinoscolapsoregion.h"
#include "algdesrefinamientomallacuadrilateros.h"
#include "algrefinamientomallacuadrilateros.h"
#include "algmejoramientomallacuadrilateros.h"

FabricaAlgoritmosMallaCuadrilateros::FabricaAlgoritmosMallaCuadrilateros() {}

AlgDesplazamiento *FabricaAlgoritmosMallaCuadrilateros::crearAlgoritmoDesplazamiento(int tipo, double val) {
    AlgDesplazamientoMallaCuadrilateros *algoritmo = NULL;
    if(tipo == 0)
        algoritmo = new NoVerificacion(val);
    if(tipo == 1)
        algoritmo = new VerificacionNodosVecinosColapsoRegion(val);
    return algoritmo;
}

AlgDesrefinamiento *FabricaAlgoritmosMallaCuadrilateros::crearAlgoritmoDesrefinamiento(int tipo) {
    AlgDesrefinamientoMallaCuadrilateros *algoritmo = NULL;
    return algoritmo;
}

AlgRefinamiento *FabricaAlgoritmosMallaCuadrilateros::crearAlgoritmoRefinamiento(int tipo) {
    AlgRefinamientoMallaCuadrilateros *algoritmo = NULL;
    return algoritmo;
}

AlgMejoramiento *FabricaAlgoritmosMallaCuadrilateros::crearAlgoritmoMejoramiento(int tipo) {
    AlgMejoramientoMallaCuadrilateros *algoritmo = NULL;
    return algoritmo;
}

vector<string> FabricaAlgoritmosMallaCuadrilateros::getAlgoritmosDesplazamiento() {
    vector<string> algoritmos;
    algoritmos.push_back("Sin verificaciones");
    algoritmos.push_back("Nodos Vecinos colapsando región");
    return algoritmos;
}

vector<string> FabricaAlgoritmosMallaCuadrilateros::getAlgoritmosDesrefinamiento() {
    vector<string> algoritmos;
    return algoritmos;
}

vector<string> FabricaAlgoritmosMallaCuadrilateros::getAlgoritmosRefinamiento() {
    vector<string> algoritmos;
    return algoritmos;
}

vector<string> FabricaAlgoritmosMallaCuadrilateros::getAlgoritmosMejoramiento() {
    vector<string> algoritmos;
    return algoritmos;
}
