// generated 2006/10/2 19:39:05 CLT by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUIDialogDesrefinar.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "GUIDialogDesrefinar.hh"

#include "definiciones.h"


bool GUIDialogDesrefinar::isAreaCara(){
	return this->radiobuttonAreaCara->get_active();
	}
bool GUIDialogDesrefinar::isLargoArcos(){
	 return this->radiobuttonLargoArcos->get_active();
	}

double GUIDialogDesrefinar::areaCara(){
	return this->spinbuttonAreaCara->get_value();
	}
double GUIDialogDesrefinar::largoArcos(){
	return this->spinbuttonLargoArcos->get_value();
	}



void GUIDialogDesrefinar::on_radiobuttonAreaCara_toggled(){ 
	this->spinbuttonAreaCara->set_sensitive(true);
	this->spinbuttonLargoArcos->set_sensitive(false);
	}

void GUIDialogDesrefinar::on_radiobuttonLargoArcos_toggled(){ 
	this->spinbuttonAreaCara->set_sensitive(false);
	this->spinbuttonLargoArcos->set_sensitive(true);	
	}
