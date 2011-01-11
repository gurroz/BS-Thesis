// generated 2006/8/15 19:41:35 CLT by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUIDialogRefinar.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "GUIDialogRefinar.hh"

#include "definiciones.h"

bool GUIDialogRefinar::isLeppDelaunay(){
	return this->radiobuttonLeppDelaunay->get_active();
	}
bool GUIDialogRefinar::isDelaunayLongestEdgeBisection(){
	return this->radiobuttonDelaunayLongestEdgeBisection->get_active();
	}
bool GUIDialogRefinar::isAnguloMinimo(){
	return this->radiobuttonAnguloMinimo->get_active();
	}
bool GUIDialogRefinar::isAreaCara(){
	return this->radiobuttonAreaCara->get_active();
	}
bool GUIDialogRefinar::isLargoArcos(){
	 return this->radiobuttonLargoArcos->get_active();
	}
double GUIDialogRefinar::anguloMinimo(){
	return this->spinbuttonAnguloMinimo->get_value()*PI/180;
	}
double GUIDialogRefinar::areaCara(){
	return this->spinbuttonAreaCara->get_value();
	}
double GUIDialogRefinar::largoArcos(){
	return this->spinbuttonLargoArcos->get_value();
	}

void GUIDialogRefinar::on_radiobuttonAnguloMinimo_toggled(){ 
	this->spinbuttonAnguloMinimo->set_sensitive(true);
	this->spinbuttonAreaCara->set_sensitive(false);
	this->spinbuttonLargoArcos->set_sensitive(false);
	}

void GUIDialogRefinar::on_radiobuttonAreaCara_toggled(){ 
	this->spinbuttonAnguloMinimo->set_sensitive(false);
	this->spinbuttonAreaCara->set_sensitive(true);
	this->spinbuttonLargoArcos->set_sensitive(false);
	}

void GUIDialogRefinar::on_radiobuttonLargoArcos_toggled(){ 
	this->spinbuttonAnguloMinimo->set_sensitive(false);
	this->spinbuttonAreaCara->set_sensitive(false);
	this->spinbuttonLargoArcos->set_sensitive(true);	
	}
