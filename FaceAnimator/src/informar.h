#ifndef INFORMAR_H
#define INFORMAR_H

#include "comando.h"
#include "informacionmalla.h"

/**
@author Nicolas Silva Herrera, Ricardo Medina Diaz
*/
class Informar : public Comando {
    private:
        InformacionMalla *algoritmo;
		double *info;
    public:
        Informar(Malla *m);
        void execute();
		double* getInfo();
		double getLimiteMenorHistograma(int bin);
		double getLimiteMayorHistograma(int bin);
		double getFrecuenciaHistograma(int bin);
		~Informar();
};

#endif
