// generated 2006/10/25 17:57:22 CLST by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/chupacabrasx/Projects/modeladorCambiosGL/modeladorCambiosGL.glade
// for gtk 2.8.20 and gtkmm 2.8.8
//
// Please modify the corresponding derived classes in ./src/GUIDialogInformacion.hh and./src/GUIDialogInformacion.cc

#ifndef _GUIDIALOGINFORMACION_GLADE_HH
#  define _GUIDIALOGINFORMACION_GLADE_HH


#if !defined(GLADEMM_DATA)
#define GLADEMM_DATA 
#include <gtkmm/accelgroup.h>

class GlademmData
{  
        
        Glib::RefPtr<Gtk::AccelGroup> accgrp;
public:
        
        GlademmData(Glib::RefPtr<Gtk::AccelGroup> ag) : accgrp(ag)
        {  
        }
        
        Glib::RefPtr<Gtk::AccelGroup>  getAccelGroup()
        {  return accgrp;
        }
};
#endif //GLADEMM_DATA

#include <gtkmm/dialog.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/label.h>
#include <gtkmm/table.h>
#include <gtkmm/alignment.h>
#include <gtkmm/frame.h>
#include <gtkmm/box.h>

class GUIDialogInformacion_glade : public Gtk::Dialog
{  
        
        GlademmData *gmm_data;
public:
        class Gtk::Dialog * GUIDialogInformacion;
        class Gtk::Button * closebutton1;
        class Gtk::Label * label28;
        class Gtk::Label * labelNumCaras;
        class Gtk::Label * label30;
        class Gtk::Label * label31;
        class Gtk::Label * labelNumArcos;
        class Gtk::Label * labelNumNodos;
        class Gtk::Table * table5;
        class Gtk::Alignment * alignment7;
        class Gtk::Label * label24;
        class Gtk::Frame * frame7;
        class Gtk::Label * label34;
        class Gtk::Label * label35;
        class Gtk::Label * label36;
        class Gtk::Label * labelAreaMinima;
        class Gtk::Label * labelAreaMaxima;
        class Gtk::Label * labelAreaPromedio;
        class Gtk::Label * label40;
        class Gtk::Label * label41;
        class Gtk::Label * labelAnguloMinimo;
        class Gtk::Label * labelAnguloMaximo;
        class Gtk::Table * table6;
        class Gtk::Label * label42;
        class Gtk::Label * labelRango0;
        class Gtk::Label * labelRango2;
        class Gtk::Label * labelRango3;
        class Gtk::Label * labelRango4;
        class Gtk::Label * labelRango5;
        class Gtk::Label * labelRango6;
        class Gtk::Label * labelRango7;
        class Gtk::Label * labelRango8;
        class Gtk::Label * labelRango9;
        class Gtk::Label * labelRango1;
        class Gtk::Label * labelFrecuencia0;
        class Gtk::Label * labelFrecuencia1;
        class Gtk::Label * labelFrecuencia2;
        class Gtk::Label * label43;
        class Gtk::Label * label44;
        class Gtk::Label * labelFrecuencia3;
        class Gtk::Label * labelFrecuencia4;
        class Gtk::Label * labelFrecuencia5;
        class Gtk::Label * labelFrecuencia6;
        class Gtk::Label * labelFrecuencia7;
        class Gtk::Label * labelFrecuencia8;
        class Gtk::Label * labelFrecuencia9;
        class Gtk::Table * table8;
        class Gtk::VBox * vbox8;
        class Gtk::Alignment * alignment8;
        class Gtk::Label * label25;
        class Gtk::Frame * frame8;
        class Gtk::Label * label37;
        class Gtk::Label * label38;
        class Gtk::Label * label39;
        class Gtk::Label * labelArcoMinimo;
        class Gtk::Label * labelArcoMaximo;
        class Gtk::Label * labelArcoPromedio;
        class Gtk::Table * table7;
        class Gtk::Alignment * alignment9;
        class Gtk::Label * label26;
        class Gtk::Frame * frame9;
        class Gtk::VBox * vbox7;
protected:
        
        GUIDialogInformacion_glade();
        
        ~GUIDialogInformacion_glade();
private:
        virtual void on_closebutton1_clicked() = 0;
};
#endif