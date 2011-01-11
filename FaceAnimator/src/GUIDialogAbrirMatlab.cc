// generated 2006/7/30 14:12:09 CLT by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUIDialogAbrirMatlab.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "GUIDialogAbrirMatlab.hh"

GUIDialogAbrirMatlab::GUIDialogAbrirMatlab(){
	comboTipoMalla->get_entry()->set_text("Triangulos");
	}

int GUIDialogAbrirMatlab::getNumeroDeAnillos(){
	return spinbuttonNumeroDeAnillos->get_value_as_int();
	}
int GUIDialogAbrirMatlab::getPuntosPorAnillo(){
	return spinbuttonPuntosPorAnillo->get_value_as_int();
	}
string GUIDialogAbrirMatlab::getTipoMalla(){
	return comboTipoMalla->get_entry()->get_text();
	}
