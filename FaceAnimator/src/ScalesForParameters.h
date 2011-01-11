

#ifndef _SCALESFORPARAMETERS_H
#  define _SCALESFORPARAMETERS_H

#if defined __GNUC__ && __GNUC__ < 3
#error This program will crash if compiled with g++ 2.x
// see the dynamic_cast bug in the gtkmm FAQ
#endif //
#include "config.h"
#include <gtkmmconfig.h>
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
//#include <sigc++/compatibility.h>
#define GMM_GTKMM_22_24(a,b) b
#else //gtkmm 2.2
#define GMM_GTKMM_22_24(a,b) a
#endif //



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


#include <gtkmm/label.h>
#include <gtkmm/scale.h>
#include <gtkmm/box.h>
using namespace std;

class ScalesForParameters : public Gtk::HBox {
    GlademmData *gmm_data;

    private:
        class Gtk::HScale * *hscale;     // arreglo de HScales de tamaño variable
        class Gtk::Label * *label;       // arreglo de Labels de tamaño variable
        double *values;                  // arreglo de doubles de tamaño variable

        class Gtk::VBox * vbox1;
        class Gtk::VBox * vbox2;
        int N;
    public:
        ScalesForParameters(string* names, int N, bool show_numbers = true);

        template <class T_obj>
        void signal_value_changed_connect(T_obj* obj, void (T_obj::*function)(int)){
            for(int i = 0; i<N; ++i){
                hscale[i]->signal_value_changed().connect(
                    sigc::bind<int>( sigc::mem_fun(*obj, function), i), false);
            }
        };

        void on_hscale_value_changed(int i);
        double get_value(int i);
        void set_value(int i, double value);
        double get_dif(int i);
        void reset();
        ~ScalesForParameters();
};

#endif
