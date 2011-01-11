#ifndef LEPP_H
#define LEPP_H

#include <vector>
#include "malla.h"

/**
@author Nicolas Silva Herrera
algoritmo para encontrar el Lepp de una cara
 */

class Lepp {
    public:
        vector<int> findLepp(Malla *malla, int ind_cara);
};

#endif
