// generated 2009/4/8 17:28:30 CLT by rvalenzu@rvalenzu-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUIDialogInicio.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "GUIDialogInicio.hh"

void GUIDialogInicio::on_button1_clicked()
{
    tree = false;
    this->hide();
}

void GUIDialogInicio::on_button2_clicked()
{
    tree = true;
    this->hide();
}

bool GUIDialogInicio::initTreeGrowth(){
    return tree;
}

bool GUIDialogInicio::initFace(){
    return !tree;
}
