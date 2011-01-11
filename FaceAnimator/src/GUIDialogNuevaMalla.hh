// generated 2006/7/31 20:29:09 CLT by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUIDialogNuevaMalla.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _GUIDIALOGNUEVAMALLA_HH
#  include "GUIDialogNuevaMalla_glade.hh"
#include <gtkmm/comboboxtext.h>
#  include <string>
#  define _GUIDIALOGNUEVAMALLA_HH

using namespace std;
class GUIDialogNuevaMalla : public GUIDialogNuevaMalla_glade{
	public:
		GUIDialogNuevaMalla();
		int getAltura();
		int getRadio();
		int getNumeroDeAnillos();
		int getPuntosPorAnillo();
		string getTipoMalla();
		string getTipoFigura();
		string getMedulaArchivo();

		void on_combo_entryTipoFigura_changed();
		void on_buttonMedulaExplorarArchivo_clicked();

};
#endif
