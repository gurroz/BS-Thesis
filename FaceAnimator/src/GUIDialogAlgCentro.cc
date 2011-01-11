// generated 2008/4/16 15:48:09 CLT by cristi@cristi-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUIDialogAlgCentro.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "GUIDialogAlgCentro.hh"

GUIDialogAlgCentro::GUIDialogAlgCentro(){
    this->comboAlgoritmoCentro->get_entry()->set_text("Baricentro");
}

string GUIDialogAlgCentro::getAlgCentro(){
    return this->comboAlgoritmoCentro->get_entry()->get_text();
}
