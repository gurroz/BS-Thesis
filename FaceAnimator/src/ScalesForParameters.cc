
#include "ScalesForParameters.h"
#include <gdk/gdkkeysyms.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/adjustment.h>
#include <iostream>


ScalesForParameters::ScalesForParameters(string* names, int n, bool show_numbers): Gtk::HBox(true,0){
    N = n;

    label = new class Gtk::Label *[N];
    hscale = new class Gtk::HScale *[N];
    values = new double[N];


    for(int i = 0; i<N; ++i){
       //number[i] = aux[i];
       //stringstream st; st << things << number[i];
       label[i] = new class Gtk::Label((names[i]));

       Gtk::Adjustment *hscale1_adj = Gtk::manage(new class Gtk::Adjustment(0, -1, 1, 0.01, 0.1, 0));
       hscale[i] = new class Gtk::HScale(*hscale1_adj);

       label[i]->set_alignment(0.5,0.5);
       label[i]->set_padding(0,0);
       label[i]->set_justify(Gtk::JUSTIFY_LEFT);
       label[i]->set_line_wrap(false);
       label[i]->set_use_markup(false);
       label[i]->set_selectable(false);
       label[i]->set_tooltip_text(names[i]);
       hscale[i]->set_flags(Gtk::CAN_FOCUS);
       hscale[i]->set_update_policy(Gtk::UPDATE_CONTINUOUS);
       hscale[i]->set_inverted(false);
       hscale[i]->set_digits(3);
       hscale[i]->set_draw_value(show_numbers);
       hscale[i]->set_value_pos(Gtk::POS_TOP);
       values[i] = 0;
    }

    for(int i = 0; i<N; ++i){
       label[i]->show();
       hscale[i]->show();
   }
   vbox1 = new class Gtk::VBox(false, 0);
   vbox2 = new class Gtk::VBox(false, 0);


   for(int i = 0; i<N; ++i){
       vbox1->pack_start(*label[i]);
       vbox2->pack_start(*hscale[i]);
   }

   vbox1->show();
   vbox2->show();

   this->pack_start(*vbox1);
   this->pack_start(*vbox2);


   //this->set_size_request(250,560);

}

double ScalesForParameters::get_value(int i){
    values[i] = hscale[i]->get_value();
    return values[i];
}

void ScalesForParameters::set_value(int i, double value){
    hscale[i]->set_value(value);
}

double ScalesForParameters::get_dif(int i){
    double ant_val = values[i];
    values[i] = hscale[i]->get_value();
    return values[i] - ant_val;
}

void ScalesForParameters::reset(){
    for(int i = 0; i<N; ++i){
        hscale[i]->set_value(0);
    }
}

ScalesForParameters::~ScalesForParameters(){
  for(int i = 0; i< N; ++i){
     delete hscale[i];
     delete label[i];
  }
 delete[] hscale;
 delete[] label;
 delete[] values;
 delete vbox1;
 delete vbox2;
}
