#ifndef DESREFINAMIENTOEDGECOLLAPSE_H
#define DESREFINAMIENTOEDGECOLLAPSE_H

#include "algdesrefinamientomallatriangulos.h"

/**
@author Nicolas Silva Herrera
algoritmo de desrefinamiento basado en Edge Collapse
 */
class DesrefinamientoEdgeCollapse : public AlgDesrefinamientoMallaTriangulos {
    public:
        void aplicar(Malla *malla, Criterio *criterio);
	private:
		vector<int> excluidos;
		int desrefinar(Malla* malla, int indCara);

};

#endif
