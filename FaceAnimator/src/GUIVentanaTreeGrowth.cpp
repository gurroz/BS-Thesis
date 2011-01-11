/**
 @author Renato Valenzuela Palominos
 */


#include "GUIVentanaTreeGrowth.hh"
#include "GUIDialogDistribuirHormona.hh"
#include "distribuirhormona.h"
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
//#include <sigc++/compatibility.h>
#define GMM_GTKMM_22_24(a,b) b
#else //gtkmm 2.2
#define GMM_GTKMM_22_24(a,b) a
#endif //

#include "GUIDialogCambios.hh"
#include "deformar.h"


 GUIVentanaTreeGrowth::GUIVentanaTreeGrowth(): GUIVentanaPrincipal("Tree Growth Simulator"){


   distribuir_hormona1 = NULL;
   separador5 = NULL;



   malla1_menu->items().push_front(Gtk::Menu_Helpers::SeparatorElem());
   separador5 = (Gtk::MenuItem *)&malla1_menu->items().front();

   image197 = Gtk::manage(new class Gtk::Image(Gtk::StockID("gtk-select-color"), Gtk::IconSize(1)));
   malla1_menu->items().push_front(Gtk::Menu_Helpers::ImageMenuElem("Distribuir Hormona...", *image197));
   distribuir_hormona1 = (Gtk::ImageMenuItem *)&malla1_menu->items().front();

   image197->set_alignment(0.5,0.5);
   image197->set_padding(0,0);


   distribuir_hormona1->show();
   separador5->show();
   image197->show();


   distribuir_hormona1->signal_activate().connect(sigc::mem_fun(*this, &GUIVentanaTreeGrowth::on_distribuir_hormona1_activate), false);


 };

void GUIVentanaTreeGrowth::on_distribuir_hormona1_activate(){
    if(this->malla == NULL) {
		this->escribirEnLog("La malla aun no esta seteada.");
        return;
    	}

    GUIDialogDistribuirHormona dialog;
    Comando *comando=NULL;
	int result=dialog.run();
	if (result==Gtk::RESPONSE_OK){
	    double gravitacional=dialog.getGravitacional();
	    double longitudinal=dialog.getLongitudinal();
	    double tangencial=dialog.getTangencial();
        comando=new DistribuirHormona(malla,simpleglscene,gravitacional,longitudinal,tangencial);
        }
    else
        return;

    comando->execute();
    simpleglscene->updateMalla(malla,false);
    delete comando;
    this->escribirEnLog("Hormonas distribuidas.");

    }

void GUIVentanaTreeGrowth::on_deformar1_activate(){
	if(this->malla == NULL) {
		this->escribirEnLog("La malla aun no esta seteada.");
        return;
    	}

	GUIDialogCambios dialog;
	dialog.setTipoMalla(malla->getTipoMalla());
	int result=dialog.run();
	if (result==Gtk::RESPONSE_APPLY){
		Comando* comando=NULL;
		vector<string> algoritmos = malla->getFabricaAlgoritmos()->getAlgoritmosDesplazamiento();
		int tipo;
		for(tipo = 0; tipo < (int)algoritmos.size(); ++tipo)
            if(algoritmos[tipo] == dialog.getTipoVerificaciones())
                break;
		if (dialog.getTipoVerificaciones()=="Consistencia local"){
			if (dialog.getHastaPrimeraInconsistencia()==true)
				comando=new Deformar(malla,tipo,-1);
			else if (dialog.getMoverLibremente()==true)
				comando=new Deformar(malla,tipo,dialog.getPorcentajeAMover()/100);
			else
				return;
			}
		else if (tipo < (int)algoritmos.size())
			comando=new Deformar(malla,tipo,dialog.getPorcentajeAMover()/100);
		else
			return;

		//Dibujo la animacion en el visualizador.
		simpleglscene->clear();
		simpleglscene->updateAnimacion(1,malla);
		for(int i=0;i<dialog.spinbuttonPasos->get_value();i++){
            comando->execute();
			simpleglscene->updateAnimacion(i+2,malla);
			cout << "Dibujado frame " << i+2 << endl;
			}
		simpleglscene->updateMalla(malla,false);

		delete comando;

		this->escribirEnLog("Deformamiento aplicado.");
		}
	else
		return;

	}


GUIVentanaTreeGrowth::~GUIVentanaTreeGrowth(){

 };
