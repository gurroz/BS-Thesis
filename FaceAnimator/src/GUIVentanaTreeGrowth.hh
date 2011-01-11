/**
@author Renato Valenzuela Palominos
 */

#ifndef GUIVENTANATREEGROWTH_HH_INCLUDED
#define GUIVENTANATREEGROWTH_HH_INCLUDED


#  include "GUIVentanaPrincipal.hh"

using namespace std;
class GUIVentanaTreeGrowth : public GUIVentanaPrincipal
{
    private:
		//GUI_AUVSelector* win_auv;
    public:
		GUIVentanaTreeGrowth();
		~GUIVentanaTreeGrowth();

        void on_distribuir_hormona1_activate();
        void on_deformar1_activate();

};


#endif // GUIVENTANATREEGROWTH_HH_INCLUDED
