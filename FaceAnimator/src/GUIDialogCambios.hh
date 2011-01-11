// generated 2006/8/2 16:01:43 CLT by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUIDialogCambios.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _GUIDIALOGCAMBIOS_HH
#  include "GUIDialogCambios_glade.hh"
#include <gtkmm/comboboxtext.h>
#include <string>
#  define _GUIDIALOGCAMBIOS_HH

using namespace std;
class GUIDialogCambios : public GUIDialogCambios_glade
{
	public:
		GUIDialogCambios();
		string getTipoVerificaciones();
		bool getHastaPrimeraInconsistencia();
		bool getMoverLibremente();
		double getPorcentajeAMover();
		void setTipoMalla(string tipoMalla);

	private:
        string tipo_malla;
		void on_comboTipoVerificaciones_changed();
        void on_radiobuttonHastaPrimeraInconsistencia_toggled();
        void on_radiobuttonMoverLibremente_toggled();
};
#endif
