// generated 2006/7/30 14:12:09 CLT by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUIDialogAbrirMatlab.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _GUIDIALOGABRIRMATLAB_HH
#  include "GUIDialogAbrirMatlab_glade.hh"
#include <gtkmm/comboboxtext.h>
#  include <string>
#  define _GUIDIALOGABRIRMATLAB_HH

using namespace std;
class GUIDialogAbrirMatlab : public GUIDialogAbrirMatlab_glade{
	public:
		GUIDialogAbrirMatlab();
		int getNumeroDeAnillos();
		int getPuntosPorAnillo();
		string getTipoMalla();
};

#endif
