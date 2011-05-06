// generated 2006/7/27 4:04:57 CLT by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to modeladorcambios.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include <gtkmm/main.h>

#include "GUIDialogInicio.hh"
#include "GUIVentanaFaceModeling.hh"
#include "GUIVentanaTreeGrowth.hh"

int main(int argc, char **argv){

    Gtk::Main m(argc, argv);
    // Init gtkglextmm.
    Gtk::GL::init(argc, argv);

    // Query OpenGL extension version.
    int major, minor;
    Gdk::GL::query_version(major, minor);
    std::cout << "OpenGL extension version - "<< major << "." << minor << std::endl;

    /*GUIDialogInicio inicio;

    m.run(inicio);
    if(inicio.initFace()){
        GUIVentanaTreeGrowth gui;
        m.run(gui);
    }else{*/
        GUIVentanaFaceModeling gui;
        m.run(gui);
    //}



    return 0;
}
