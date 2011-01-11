#include "informacionmalla.h"
#include <limits>

InformacionMalla::InformacionMalla(){
	h = gsl_histogram_alloc (10);
	info=new double[20];
	}

void InformacionMalla::aplicar(Malla *malla){
	assert(malla!=NULL);

	info[0]=malla->getNumCaras();
	info[1]=malla->getNumArcos();
	info[2]=malla->getNumNodos();

	//Calculamos las areas y angulos de las caras.
	double areaMinima=numeric_limits<double>::max();
	double areaMaxima=0;
	double areaPromedio=0;
	double anguloMinimo=numeric_limits<double>::max();
	double anguloMaximo=0;
	for(int i=0; i<=malla->getMaxIndiceCaras(); i++){
		Cara *c = malla->getCara(i);
		if(c!=NULL){
			double area=c->getArea(malla);
			if(area<areaMinima)
				areaMinima=area;
			if (area>areaMaxima)
				areaMaxima=area;
			areaPromedio=areaPromedio+area;

			double angulo=c->getAnguloMin(malla);
			if (angulo<anguloMinimo)
				anguloMinimo=angulo;
			angulo=c->getAnguloMax(malla);
			if (angulo>anguloMaximo)
				anguloMaximo=angulo;
			}
		}
	areaPromedio=areaPromedio/malla->getNumCaras();
	info[3]=areaMinima;
	info[4]=areaMaxima;
	info[5]=areaPromedio;
	info[6]=anguloMinimo*180/PI;
	info[7]=anguloMaximo*180/PI;

	//Calculamos el histograma de las areas.
	gsl_histogram_set_ranges_uniform (h, areaMinima, areaMaxima);
	for(int i=0; i<=malla->getMaxIndiceCaras(); i++){
		Cara *c = malla->getCara(i);
		if(c!=NULL)
			gsl_histogram_increment (h, c->getArea(malla));
		}

	//Calculamos los largos de los arcos.
	double largoMinimo=numeric_limits<double>::max();
	double largoMaximo=0;
	double largoPromedio=0;
	for(int i=0; i<=malla->getMaxIndiceArcos(); i++){
		Arco *arco = malla->getArco(i);
		if(arco!=NULL){
			double largo=arco->getLargo(malla);
			if(largo<largoMinimo)
				largoMinimo=largo;
			if (largo>largoMaximo)
				largoMaximo=largo;
			largoPromedio+=largo;
			}
		}
	largoPromedio=largoPromedio/malla->getNumArcos();
	info[8]=largoMinimo;
	info[9]=largoMaximo;
	info[10]=largoPromedio;

	}

double * InformacionMalla::getInfo(){
	return info;
	}

double InformacionMalla::getLimiteMenorHistograma(int bin){
	double resultado;
	double aux;
	gsl_histogram_get_range(h,bin,&resultado,&aux);
	return resultado;
	}

double InformacionMalla::getLimiteMayorHistograma(int bin){
	double resultado;
	double aux;
	gsl_histogram_get_range(h,bin,&aux,&resultado);
	return resultado;
	}

double InformacionMalla::getFrecuenciaHistograma(int bin){
	return gsl_histogram_get(h,bin);
	}

InformacionMalla::~InformacionMalla(){
	delete info;
	gsl_histogram_free (h);
	}
