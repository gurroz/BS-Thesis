// generated 2009/4/2 18:03:34 CLT by rvalenzu@rvalenzu-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUI_AUVSelector.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "GUI_AUVSelector.hh"


GUI_AUVSelector::GUI_AUVSelector(GUIVentanaFaceModeling *ventana): GUI_AUVSelector_glade()
{
        this->father = ventana;
        values = new double[N];
        for(int i = 0; i<N; ++i){
                values[i] = 0;
        }
};

void GUI_AUVSelector::on_hscale_value_changed(int i)
{
    double ant = values[i];
    double value = things->get_value(i);
    values[i] = value;
    father->moverMallaAUV(i, value-ant);
};

void GUI_AUVSelector::reset()
{
        for(int i = 0; i<N; ++i){
            values[i] = 0;
        }
        things->reset();
};

void GUI_AUVSelector::on_cerrar_activate(){
    this->father->closedAUV();
}

GUI_AUVSelector::~GUI_AUVSelector(){
        delete[] values;
}

