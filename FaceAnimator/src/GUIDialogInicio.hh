// generated 2009/4/8 17:28:30 CLT by rvalenzu@rvalenzu-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUIDialogInicio.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _GUIDIALOGINICIO_HH
#  include "GUIDialogInicio_glade.hh"
#  define _GUIDIALOGINICIO_HH
class GUIDialogInicio : public GUIDialogInicio_glade
{
   private:
        bool tree;

   public:
        void on_button1_clicked();
        void on_button2_clicked();
        bool initTreeGrowth();
        bool initFace();
};
#endif
