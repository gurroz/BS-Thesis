#ifndef SEGTRIINT_H
#define SEGTRIINT_H

#include <vector>
#include "vect.h"
#include "segmenttriangleintersection.h"

using namespace std;

/**
@author Nicolas Silva Herrera
 Esta clase es un adaptador para el uso de funciones obtenidas del libro
 Computational Geometry in C++ de O'Rourke
 */
class AdapterComputationalGeometry {
    public:
        AdapterComputationalGeometry();
        char SegTriInt(Vect* T,Vect q,Vect r);
        char SegPlaneInt(Vect* T, Vect q, Vect r);
		~AdapterComputationalGeometry();
};

#endif
