// generated 2006/8/2 16:01:43 CLT by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUIDialogCambios.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "GUIDialogCambios.hh"

#include <iostream>

GUIDialogCambios::GUIDialogCambios(){
}

void GUIDialogCambios::setTipoMalla(string tipoMalla){
    tipo_malla = tipoMalla;
    if(tipoMalla == "triangular") {
        comboTipoVerificacionesT->get_entry()->set_text("Sin verificaciones");
        this->hboxCuadrilateros->hide();
    }
    else if(tipoMalla == "quadrilateral") {
        comboTipoVerificacionesC->get_entry()->set_text("Sin verificaciones");
        this->framePropiedades->hide();
        this->hboxTriangulos->hide();
	}
}

string GUIDialogCambios::getTipoVerificaciones(){
    string tipo;
    if(tipo_malla == "triangular")
        tipo = this->comboTipoVerificacionesT->get_entry()->get_text();
    else if(tipo_malla == "quadrilateral")
        tipo = this->comboTipoVerificacionesC->get_entry()->get_text();
    return tipo;
}

bool GUIDialogCambios::getHastaPrimeraInconsistencia(){
	return this->radiobuttonHastaPrimeraInconsistencia->get_active();
	}
bool GUIDialogCambios::getMoverLibremente(){
	return this->radiobuttonMoverLibremente->get_active();
	}

double GUIDialogCambios::getPorcentajeAMover(){
	return this->spinbuttonPorcenjateAMover->get_value();
	}

void GUIDialogCambios::on_comboTipoVerificaciones_changed(){
	if (comboTipoVerificacionesT->get_entry()->get_text()=="Consistencia local"){
		this->framePropiedades->show();
		}
	else if (comboTipoVerificacionesT->get_entry()->get_text()=="Sin verificaciones"){
		this->framePropiedades->hide();
		}
	else if (comboTipoVerificacionesT->get_entry()->get_text()=="Verificacion por Nodos Vecinos"){
		this->framePropiedades->hide();
		}
	else if (comboTipoVerificacionesT->get_entry()->get_text()=="Nodos Vecinos colapsando región"){
		this->framePropiedades->hide();
		}
	else
		return;
	}

void GUIDialogCambios::on_radiobuttonHastaPrimeraInconsistencia_toggled(){
	this->spinbuttonPorcenjateAMover->set_sensitive(false);
	this->labelPorcentajeAMover->set_sensitive(false);
	}

void GUIDialogCambios::on_radiobuttonMoverLibremente_toggled(){
	this->spinbuttonPorcenjateAMover->set_sensitive(true);
	this->labelPorcentajeAMover->set_sensitive(true);
	}
