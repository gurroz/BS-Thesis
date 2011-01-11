// generated 2006/10/2 19:39:05 CLT by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUIDialogDesrefinar.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _GUIDIALOGDESREFINAR_HH
#  include "GUIDialogDesrefinar_glade.hh"
#  define _GUIDIALOGDESREFINAR_HH
class GUIDialogDesrefinar : public GUIDialogDesrefinar_glade
{  
        
   public:
		bool isAreaCara();
		bool isLargoArcos();
		double areaCara();
		double largoArcos();
	private:        
        void on_radiobuttonAreaCara_toggled();
        void on_radiobuttonLargoArcos_toggled();
};
#endif
