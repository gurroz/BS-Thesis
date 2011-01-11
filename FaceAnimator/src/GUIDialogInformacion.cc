// generated 2006/10/20 13:55:58 CLST by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUIDialogInformacion.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "GUIDialogInformacion.hh"

#include "informacionmalla.h"

#include <sstream>

GUIDialogInformacion::GUIDialogInformacion(Informar* informar){
	
	//Obtengo la informacion.
	double *info=informar->getInfo();
	
	//Lleno la informacion.
	stringstream aux;
	
	aux << info[0];
	labelNumCaras->set_label(aux.str());
	aux.str("");
	
	aux << info[1];
	labelNumArcos->set_label(aux.str());
	aux.str("");
	
	aux << info[2];
	labelNumNodos->set_label(aux.str());
	aux.str("");
	
	aux << info[3];
	labelAreaMinima->set_label(aux.str());
	aux.str("");
	
	aux << info[4];
	labelAreaMaxima->set_label(aux.str());
	aux.str("");
	
	aux << info[5];
	labelAreaPromedio->set_label(aux.str());
	aux.str("");
	
	aux << info[6];
	labelAnguloMinimo->set_label(aux.str());
	aux.str("");
	
	aux << info[7];
	labelAnguloMaximo->set_label(aux.str());
	aux.str("");
	
	aux << info[8];
	labelArcoMinimo->set_label(aux.str());
	aux.str("");
	
	aux << info[9];
	labelArcoMaximo->set_label(aux.str());
	aux.str("");
	
	aux << info[10];
	labelArcoPromedio->set_label(aux.str());
	aux.str("");
	
	
	//Llenamos el histograma de areas:
	aux << informar->getLimiteMenorHistograma(0) << " - " << informar->getLimiteMayorHistograma(0);
	labelRango0->set_label(aux.str());
	aux.str("");
	aux << informar->getFrecuenciaHistograma(0);
	labelFrecuencia0->set_label(aux.str());
	aux.str("");
	
	aux << informar->getLimiteMenorHistograma(1) << " - " << informar->getLimiteMayorHistograma(1);
	labelRango1->set_label(aux.str());
	aux.str("");
	aux << informar->getFrecuenciaHistograma(1);
	labelFrecuencia1->set_label(aux.str());
	aux.str("");
	
	aux << informar->getLimiteMenorHistograma(2) << " - " << informar->getLimiteMayorHistograma(2);
	labelRango2->set_label(aux.str());
	aux.str("");
	aux << informar->getFrecuenciaHistograma(2);
	labelFrecuencia2->set_label(aux.str());
	aux.str("");
	
	aux << informar->getLimiteMenorHistograma(3) << " - " << informar->getLimiteMayorHistograma(3);
	labelRango3->set_label(aux.str());
	aux.str("");
	aux << informar->getFrecuenciaHistograma(3);
	labelFrecuencia3->set_label(aux.str());
	aux.str("");
	
	aux << informar->getLimiteMenorHistograma(4) << " - " << informar->getLimiteMayorHistograma(4);
	labelRango4->set_label(aux.str());
	aux.str("");
	aux << informar->getFrecuenciaHistograma(4);
	labelFrecuencia4->set_label(aux.str());
	aux.str("");
	
	aux << informar->getLimiteMenorHistograma(5) << " - " << informar->getLimiteMayorHistograma(5);
	labelRango5->set_label(aux.str());
	aux.str("");
	aux << informar->getFrecuenciaHistograma(5);
	labelFrecuencia5->set_label(aux.str());
	aux.str("");
	
	aux << informar->getLimiteMenorHistograma(6) << " - " << informar->getLimiteMayorHistograma(6);
	labelRango6->set_label(aux.str());
	aux.str("");
	aux << informar->getFrecuenciaHistograma(6);
	labelFrecuencia6->set_label(aux.str());
	aux.str("");
	
	aux << informar->getLimiteMenorHistograma(7) << " - " << informar->getLimiteMayorHistograma(7);
	labelRango7->set_label(aux.str());
	aux.str("");
	aux << informar->getFrecuenciaHistograma(7);
	labelFrecuencia7->set_label(aux.str());
	aux.str("");
	
	aux << informar->getLimiteMenorHistograma(8) << " - " << informar->getLimiteMayorHistograma(8);
	labelRango8->set_label(aux.str());
	aux.str("");
	aux << informar->getFrecuenciaHistograma(8);
	labelFrecuencia8->set_label(aux.str());
	aux.str("");
	
	aux << informar->getLimiteMenorHistograma(9) << " - " << informar->getLimiteMayorHistograma(9);
	labelRango9->set_label(aux.str());
	aux.str("");
	aux << informar->getFrecuenciaHistograma(9);
	labelFrecuencia9->set_label(aux.str());
	aux.str("");
	}

void GUIDialogInformacion::on_closebutton1_clicked(){
	hide();
	}
