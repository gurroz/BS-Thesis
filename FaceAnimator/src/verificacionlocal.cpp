#include "verificacionlocal.h"
#include "mallatriangulos.h"

VerificacionLocal::VerificacionLocal(double val) : AlgDesplazamientoMallaTriangulos() {
    this->val = val;
}

void VerificacionLocal::aplicar(Malla *malla) {
    double mov=0;
    if(val == -1) {
        mov = moverHastaPrimeraInconsistencia(malla);
    }
    else if(val >= 0) {
        mov = moverHasta(malla);
    }
    cout << "Malla movida una proporcion = " << mov << endl;
}

double VerificacionLocal::moverHastaPrimeraInconsistencia(Malla *malla) {
	//@todo: agregar assert que verifique que la malla es de triángulos
	MallaTriangulos *malla_t = (MallaTriangulos *)malla;
    double min_vol_cero = 1; // minima distancia a mover
    double min_raiz_arco;
    int arco_min = -1;
    vector<double> raices;
    //recorremos los arcos de la malla buscando donde se produce la primera inconsistencia.
    for(int i=0; i<=malla_t->getMaxIndiceArcos(); i++) {
        if(malla_t->getArco(i) != 0) {
            //obtenemos la lista de valores donde el volumen se hace 0 para la región local de ese arco.
            raices = malla_t->getValoresVolumenCero(i);
            if(raices.size() > 0) {
				//Se encontraron raices
                //obtenemos la raiz menor de ese arco.
                min_raiz_arco = 1.0;
                for(int j=0; j<(int)raices.size(); j++) {
					//Habra inconsistencia en la proporcion raices[j]
                    if(raices[j] > 0 && raices[j] < min_raiz_arco) {
                        min_raiz_arco = raices[j];
                    }
                }
                //en t=1.0 se mueve una distancia igual a su concentración.
                if(min_raiz_arco < min_vol_cero) {
                    int tipo = malla_t->getTipoMovRegion(i,min_raiz_arco);
                    //Inconsistencia en arco i en la proporcion min_raiz_arco
                    // si es TIP_OUTSIDE_B no hay problema.
                    if(tipo != TIP_OUTSIDE_B) {
                        min_vol_cero = min_raiz_arco;
                        arco_min = i;
                    }
                }
            }
        }
    }

    malla_t->moverNodosSegunConcentracion(min_vol_cero); // se mueve una cierta proporción de su concentración.

    cout << "Arco inconsistente: " << arco_min << endl;

    //manejamos la inconsistencia que se produce en ese arco.
    if(arco_min != -1) {
        malla_t->manejaInconsitenciaArco(arco_min);
    }

    //retornamos el valor que movimos (en proporcion) la malla.
    return min_vol_cero;
}

double VerificacionLocal::moverHasta(Malla *malla) {
	//@todo: agregar assert que verifique que la malla es de triángulos
	MallaTriangulos *malla_t = (MallaTriangulos *)malla;
    map<int, double> arco_raiz;
    map<int, double>::iterator iter1;
    map<int, double>::iterator iter2;

    vector<int> arcos_inconsistentes;

    double min_vol_arco;
    vector<double> raices;
    for(int i=0; i<=malla_t->getMaxIndiceArcos(); i++) {
        if(malla_t->getArco(i) != 0) {
            //obtenemos la lista de valores donde el volumen se hace 0 para la región local de ese arco.
            raices = malla_t->getValoresVolumenCero(i);
            if(raices.size() > 0) {
                //obtenemos la raiz menor de ese arco.
                min_vol_arco = val;
                for(int j=0; j<(int)raices.size(); j++) {
                    if(raices[j] > 0 && raices[j] < min_vol_arco) {
                        min_vol_arco = raices[j];
                    }
                }
                if(min_vol_arco < val) {
                    int tipo = malla->getTipoMovRegion(i,min_vol_arco);
					//Inconsistencia en arco i << " en la proporcion " << min_vol_arco << ", TIPO = " << tipo<< endl;
                    if(tipo != TIP_OUTSIDE_B) {
                        arcos_inconsistentes.push_back(i);
                        arco_raiz.insert(make_pair(i,min_vol_arco));
                    }
                }
            }
        }
    }

    // ordenamos los arcos de menor a mayor según su raiz.
    int k = arcos_inconsistentes.size();
    cout << "Numero de arcos inconsistentes = " << arcos_inconsistentes.size() << endl;
    while(k > 1) {
        int i=0;
        for(int j=0; j<=k-2; j++) {
            iter1 = arco_raiz.find(arcos_inconsistentes[j]);
            iter2 = arco_raiz.find(arcos_inconsistentes[j+1]);
            if(iter1->second > iter2->second) {
                int aux = arcos_inconsistentes[j];
                arcos_inconsistentes[j] = arcos_inconsistentes[j+1];
                arcos_inconsistentes[j+1] = aux;
                i=j+1;
            }
        }
        k=i;
    }

    double dist_movida = 0;
    if(arcos_inconsistentes.size() > 0) {
        for(int i=0; i<(int)arcos_inconsistentes.size(); i++) {
            iter1 = arco_raiz.find(arcos_inconsistentes[i]);
            cout << "Arco(" << arcos_inconsistentes[i] << ") = " << iter1->second << endl;
            malla_t->moverNodosSegunConcentracion(iter1->second - dist_movida);
            dist_movida = iter1->second;
            if(malla_t->getArco(arcos_inconsistentes[i]) != 0) {
                malla_t->manejaInconsitenciaArco(arcos_inconsistentes[i]);
            }
        }
    }
    else {
        malla_t->moverNodosSegunConcentracion(val);
    }

    return val;
}
