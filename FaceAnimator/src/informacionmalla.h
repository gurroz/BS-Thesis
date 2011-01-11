#ifndef INFORMACIONMALLA_H
#define INFORMACIONMALLA_H

#include <gsl/gsl_histogram.h>

#include "malla.h"

/**
@author Nicolas Silva Herrera
Clase que devuelve informacion sobre la malla dada.
 */
class InformacionMalla {
    public:
		InformacionMalla();
        void aplicar(Malla *malla);
		double *getInfo();
		//Devuelve informacion sobre malla y lo almacena en el arreglo apuntado por info.
		//La informacion esta estructurada en info de la siguiente manera:
		//info[0]=Numero de caras
		//info[1]=Numero de arcos
		//info[2]=Numero de nodos
		//info[3]=Area minima de una cara
		//info[4]=Area maxima de una cara
		//info[5]=Area promedio de las caras
		//info[6]=Angulo minimo de una cara. (Expresado en grados)
		//info[7]=Angulo maximo de una cara. (Expresado en grados)
		//info[8]=Largo minimo de un arco
		//info[9]=Largo maximo de un arco
		//info[10]=Largo promedio de los arcos
		double getLimiteMenorHistograma(int bin);
		double getLimiteMayorHistograma(int bin);
		double getFrecuenciaHistograma(int bin);
		~InformacionMalla();
	private:
		gsl_histogram * h;
		double *info;
};

#endif
