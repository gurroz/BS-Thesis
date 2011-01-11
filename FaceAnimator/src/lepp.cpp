#include "lepp.h"

vector<int> Lepp::findLepp(Malla *malla, int ind_cara){
	//asserts
    vector<int> leep;
    int ind_cara_actual = ind_cara;
    int ind_arco_mas_largo_actual = malla->getCara(ind_cara_actual)->getArcoMasLargo(malla);
    leep.push_back(ind_cara_actual);
    int ind_cara_siguiente, ind_arco_mas_largo_siguiente;
    while(true) {
        ind_cara_siguiente = malla->getSiguienteCara(ind_arco_mas_largo_actual,ind_cara_actual);
        if(ind_cara_siguiente == -1) {
            return leep;
        }
        leep.push_back(ind_cara_siguiente);
        ind_arco_mas_largo_siguiente = malla->getCara(ind_cara_siguiente)->getArcoMasLargo(malla);
        if(ind_arco_mas_largo_actual == ind_arco_mas_largo_siguiente) {
            return leep;
        }
        ind_cara_actual = ind_cara_siguiente;
        ind_arco_mas_largo_actual = ind_arco_mas_largo_siguiente;
    }
    return leep;
	}
