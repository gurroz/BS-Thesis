/**
@author Renato Valenzuela Palominos
 */


#ifndef _GUIVENTANAFACEMODELING_HH
#  define _GUIVENTANAFACEMODELING_HH

#  include "GUIVentanaPrincipal.hh"

class GUI_AUVSelector;
#  include "GUI_AUVSelector.hh"
#  include "interpolador.h"
#  include "algdesplazamientomallatriangulos.h"

using namespace std;
class GUIVentanaFaceModeling : public GUIVentanaPrincipal
{
    private:
		GUI_AUVSelector* win_auv;
		class Gtk::CheckMenuItem * mostrar_auv1;
        Interpolador *interpolador;
        AlgDesplazamientoMallaTriangulos *movimientos;
        double* value_ant;
    protected:
        bool procesar_malla();
    public:
		GUIVentanaFaceModeling();
		~GUIVentanaFaceModeling();
		void on_abrir1_activate();
		void moverMallaAUV(int i, double value);
		void moverShapeUnit(int i, double value);
		void on_mostrar_auv1_activate();
		void on_deformar1_activate();
		void moveFromFile(string name);
		void closedAUV();


};
#endif
