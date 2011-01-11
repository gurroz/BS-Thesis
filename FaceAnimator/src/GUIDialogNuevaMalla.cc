// generated 2006/7/31 20:29:09 CLT by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUIDialogNuevaMalla.cc_new

// This file is for your program, I won't touch it again!

#include <gtkmm.h>
//#include <fstream>

#include "config.h"
#include "GUIDialogNuevaMalla.hh"


GUIDialogNuevaMalla::GUIDialogNuevaMalla(){
	comboTipoMalla->get_entry()->set_text("Triangulos");
	comboMedulaTipoMalla->get_entry()->set_text("Triangulos");
	comboTipoFigura->get_entry()->set_text("A partir de Medula");
	}

int GUIDialogNuevaMalla::getAltura(){
	return spinbuttonAltura->get_value_as_int();
	}

int GUIDialogNuevaMalla::getRadio(){
    int radio=0;
    if (getTipoFigura()=="Cilindro")
        radio=spinbuttonRadio->get_value_as_int();
    else if (getTipoFigura()=="A partir de Medula")
        radio=spinbuttonMedulaRadio->get_value_as_int();
    return radio;
	}

int GUIDialogNuevaMalla::getNumeroDeAnillos(){
	int numeroDeAnillos=0;
    if (getTipoFigura()=="Cilindro")
        numeroDeAnillos=spinbuttonNumeroDeAnillos->get_value_as_int();
    else if (getTipoFigura()=="A partir de Medula")
        numeroDeAnillos=spinbuttonMedulaNumeroDeAnillos->get_value_as_int();
    return numeroDeAnillos;
	}

int GUIDialogNuevaMalla::getPuntosPorAnillo(){
	int puntosPorAnillo=0;
    if (getTipoFigura()=="Cilindro")
        puntosPorAnillo=spinbuttonPuntosPorAnillo->get_value_as_int();
    else if (getTipoFigura()=="A partir de Medula")
        puntosPorAnillo=spinbuttonMedulaPuntosPorAnillo->get_value_as_int();
    return puntosPorAnillo;
	}

string GUIDialogNuevaMalla::getTipoMalla(){
    string tipo;
    if (getTipoFigura()=="Cilindro")
        tipo=comboTipoMalla->get_entry()->get_text();
    else if (getTipoFigura()=="A partir de Medula")
        tipo=comboMedulaTipoMalla->get_entry()->get_text();
    return tipo;
	}

string GUIDialogNuevaMalla::getTipoFigura(){
	return comboTipoFigura->get_entry()->get_text();
	}

void GUIDialogNuevaMalla::on_combo_entryTipoFigura_changed(){
    if (getTipoFigura()=="Cilindro"){
        frameCilindro->show();
        frameMedula->hide();
        }
    else if (getTipoFigura()=="A partir de Medula"){
        frameCilindro->hide();
        frameMedula->show();
        }
    }

string GUIDialogNuevaMalla::getMedulaArchivo(){
    return entryMedulaArchivo->get_text();
    }
#include <iostream>
void GUIDialogNuevaMalla::on_buttonMedulaExplorarArchivo_clicked(){
    Gtk::FileChooserDialog dialog("Abrir medula", Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  	dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
    int result = dialog.run();
    if (result==Gtk::RESPONSE_OK){
        string archivo=dialog.get_filename();
        entryMedulaArchivo->set_text(archivo);
        /*ifstream in(archivo.c_str());
        if (!in.good()) return;
        int contadorPuntos=0;
        char line[256];
        while(true){
            in.getline(line,256);
            if (in.fail()) break;
            contadorPuntos++;
            }
        in.close();
        cerr << contadorPuntos << endl;
        spinbuttonMedulaNumeroDeAnillos->set_value(contadorPuntos);*/
        }
    else
        return;
    }
