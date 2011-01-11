// generated 2009/4/2 18:03:34 CLT by rvalenzu@rvalenzu-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUI_AUVSelector.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _GUI_AUVSELECTOR_HH

#  include "GUI_AUVSelector_glade.hh"
#  define _GUI_AUVSELECTOR_HH

class GUIVentanaFaceModeling;
#  include "GUIVentanaFaceModeling.hh"

class GUI_AUVSelector : public GUI_AUVSelector_glade
{
    protected:
        GUIVentanaFaceModeling* father;
        double *values;
        static const int N = 11;
    public:
        GUI_AUVSelector(GUIVentanaFaceModeling* ventana);
        void on_hscale_value_changed(int i);
        void reset();
        void on_cerrar_activate();
        ~GUI_AUVSelector();
//        void on_hscale1_value_changed();

};
#endif
