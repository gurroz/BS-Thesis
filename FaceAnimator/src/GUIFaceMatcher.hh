// generated 2009/5/21 18:32:37 CLT by rvalenzu@rvalenzu-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUIFaceMatcher.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _GUIFACEMATCHER_HH
#  include "GUIFaceMatcher_glade.hh"
#  define _GUIFACEMATCHER_HH

#  include "SimpleGLSceneSecundario.hh"
#  include "SimpleGLScenePrimario.hh"
#  include "malla.h"

class GUIFaceMatcher : public GUIFaceMatcher_glade
{
    private:
        Malla *malla;
        SimpleGLScenePrimario *drawingArea1;
        SimpleGLSceneSecundario *drawingArea2;
        void parameter_change(int i);
        void parameter_change2(int i);
        void zoom();
        void change_pos();
        void change_angle();
        void fill_nodos_marcados();
        void guardarVariables(string file);
        void cargarVariables(string file);
        void on_open_configuration1_activate();;
        void on_save_configuration1_activate();
        void on_ok1_activate();
        void on_quit1_activate();
    public:
        GUIFaceMatcher(Malla *m, Malla *modelo);
        int *nodos_marcados;
        Malla * getModelo();
        ~GUIFaceMatcher();
        bool on_delete_event(GdkEventAny * 	event);
};
#endif
