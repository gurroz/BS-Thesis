// generated 2006/10/20 13:55:58 CLST by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUIDialogInformacion.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _GUIDIALOGINFORMACION_HH
#  include "GUIDialogInformacion_glade.hh"
#  define _GUIDIALOGINFORMACION_HH

#include "informar.h"

using namespace std;
class GUIDialogInformacion : public GUIDialogInformacion_glade{  
	public:
		GUIDialogInformacion(Informar* informar);
	private:
		void on_closebutton1_clicked();
	
	};
#endif
