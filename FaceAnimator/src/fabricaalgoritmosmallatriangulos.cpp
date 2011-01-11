#include "fabricaalgoritmosmallatriangulos.h"
#include "noverificacion.h"
#include "verificacionlocal.h"
#include "verificacionnodosvecinos.h"
#include "verificacionnodosvecinoscolapsoregion.h"
#include "desrefinamientoedgecollapse.h"
#include "leppdelaunay.h"
#include "delaunaylongestedgebisection.h"
#include "mejdelaunay.h"

FabricaAlgoritmosMallaTriangulos::FabricaAlgoritmosMallaTriangulos() {}

AlgDesplazamiento *FabricaAlgoritmosMallaTriangulos::crearAlgoritmoDesplazamiento(int tipo, double val) {
    AlgDesplazamientoMallaTriangulos *algoritmo = NULL;
    if(tipo == 0)
        algoritmo = new NoVerificacion(val);
    else if(tipo == 1)
        algoritmo = new VerificacionLocal(val);
    else if (tipo == 2)
        algoritmo = new VerificacionNodosVecinos(val);
    else if (tipo == 3)
        algoritmo = new VerificacionNodosVecinosColapsoRegion(val);
    return algoritmo;
}

AlgDesrefinamiento *FabricaAlgoritmosMallaTriangulos::crearAlgoritmoDesrefinamiento(int tipo) {
    AlgDesrefinamientoMallaTriangulos *algoritmo = NULL;
    if(tipo == 0)
        algoritmo = new DesrefinamientoEdgeCollapse();
    return algoritmo;
}

AlgRefinamiento *FabricaAlgoritmosMallaTriangulos::crearAlgoritmoRefinamiento(int tipo) {
    AlgRefinamientoMallaTriangulos *algoritmo = NULL;
    if(tipo == 0)
        algoritmo = new LeppDelaunay();
    else if(tipo == 1)
        algoritmo = new DelaunayLongestEdgeBisection();
    return algoritmo;
}

AlgMejoramiento *FabricaAlgoritmosMallaTriangulos::crearAlgoritmoMejoramiento(int tipo) {
    AlgMejoramientoMallaTriangulos *algoritmo = NULL;
    if(tipo == 0)
        algoritmo = new MejDelaunay();
    return algoritmo;
}

vector<string> FabricaAlgoritmosMallaTriangulos::getAlgoritmosDesplazamiento() {
    vector<string> algoritmos;
    algoritmos.push_back("Sin verificaciones");
    algoritmos.push_back("Consistencia local");
    algoritmos.push_back("Verificación por Nodos Vecinos borrando nodo");
    algoritmos.push_back("Nodos Vecinos colapsando región");
    return algoritmos;
}

vector<string> FabricaAlgoritmosMallaTriangulos::getAlgoritmosDesrefinamiento() {
    vector<string> algoritmos;
    algoritmos.push_back("Lepp-Delaunay");
    algoritmos.push_back("Delaunay Longest Edge Bisection");
    return algoritmos;
}

vector<string> FabricaAlgoritmosMallaTriangulos::getAlgoritmosRefinamiento() {
    vector<string> algoritmos;
    algoritmos.push_back("");
    return algoritmos;
}

vector<string> FabricaAlgoritmosMallaTriangulos::getAlgoritmosMejoramiento() {
    vector<string> algoritmos;
    algoritmos.push_back("");
    return algoritmos;
}
