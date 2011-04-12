/**
@author Nicolas Silva Herrera (TreeGrowth), Renato Valenzuela (Face Animator)
 */

#include "config.h"
#include "GUIVentanaPrincipal.hh"
#include "GUIDialogAbrirMatlab.hh"
#include "GUIDialogNuevaMalla.hh"
#include "GUIDialogRefinar.hh"
#include "GUIDialogDesrefinar.hh"
#include "GUIDialogInformacion.hh"
#include "GUIDialogAlgCentro.hh"
#include "GUI_AUVSelector.hh"

#include "comando.h"
#include "generarmallainicial.h"
#include "mejorar.h"
#include "guardar.h"
#include "refinar.h"
#include "desrefinar.h"
#include "informar.h"
#include "cuadrangular.h"
#include "triangular.h"
#include "algcentrotriangulo.h"
#include "baricentro.h"

#include <gtkmm.h>
#include <string>
#include <list>
#include <sstream>
#include <fstream>

GUIVentanaPrincipal::GUIVentanaPrincipal(string title){
	this->malla=NULL;

	this->velocidadAnimacion=150;

	simpleglscene=new GLMainScene();
	simpleglscene->setMuestraCaras(this->mostrar_caras1->get_active());
	simpleglscene->setMuestraArcos(this->mostrar_arcos1->get_active());
	vboxDrawingArea->add(*simpleglscene);
	simpleglscene->show();
	n = 0;
    this->set_title(title);

    this->dialog_abrir = createDialogAbrir();

}

Gtk::FileChooserDialog* GUIVentanaPrincipal::createDialogAbrir(){

	Gtk::FileChooserDialog* dialog = new Gtk::FileChooserDialog("Abrir malla", Gtk::FILE_CHOOSER_ACTION_OPEN);
  	dialog->set_transient_for(*this);
	dialog->set_select_multiple(true);

  	//Add response buttons the the dialog:
  	dialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  	dialog->add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

  	//Add filters, so that only certain file types can be selected:

  	Gtk::FileFilter* filter_wrl = new Gtk::FileFilter();
  	filter_wrl->set_name("wrl (VRML)");
  	filter_wrl->add_pattern("*.wrl");
  	dialog->add_filter(*filter_wrl);

  	Gtk::FileFilter* filter_wfm = new Gtk::FileFilter();
  	filter_wfm->set_name("wfm (WFM)");
  	filter_wfm->add_pattern("*.wfm");
  	dialog->add_filter(*filter_wfm);

  	Gtk::FileFilter* filter_geomview = new Gtk::FileFilter();
  	filter_geomview->set_name("off (Geomview)");
  	filter_geomview->add_pattern("*.off");
  	dialog->add_filter(*filter_geomview);

  	Gtk::FileFilter* filter_matlab = new Gtk::FileFilter();
  	filter_matlab->set_name("txt (Matlab)");
  	filter_matlab->add_pattern("*.txt");
  	dialog->add_filter(*filter_matlab);

  	Gtk::FileFilter* filter_nxnynzu = new Gtk::FileFilter();
  	filter_nxnynzu->set_name("txt (nx,ny,nz,u)");
  	filter_nxnynzu->add_pattern("*.txt");
  	dialog->add_filter(*filter_nxnynzu);

	Gtk::FileFilter* filter_comsol_1 = new Gtk::FileFilter();
  	filter_comsol_1->set_name("cms_1 (comsol_1)");
  	filter_comsol_1->add_pattern("*.cms_1");
  	dialog->add_filter(*filter_comsol_1);

  	return dialog;
}


void GUIVentanaPrincipal::on_nuevo1_activate(){
	GUIDialogNuevaMalla dialog;
	dialog.set_transient_for(*this);
	int result=dialog.run();
	if (result==Gtk::RESPONSE_OK){
		Comando *comando=NULL;
		if (dialog.getTipoFigura()=="Cilindro"){
			int tipo=10;
			int altura=dialog.getAltura();
			int radio=dialog.getRadio();
			int num_anillos=dialog.getNumeroDeAnillos();
			int num_puntos=dialog.getPuntosPorAnillo();
			int tipoMalla;
			if (dialog.getTipoMalla()=="Triangulos")
				tipoMalla=0;
			else if (dialog.getTipoMalla()=="Cuadrilateros")
				tipoMalla=1;
			else
				return;
			comando=new GenerarMallaInicial(tipo, altura, radio, num_anillos, num_puntos, tipoMalla);
			}
        else if (dialog.getTipoFigura()=="A partir de Medula"){
			int tipo=20;
			string archivo=dialog.getMedulaArchivo();
			ifstream in(archivo.c_str());
			if (!in.good()) return;
			in.close();
			int radio=dialog.getRadio();
			int num_anillos=dialog.getNumeroDeAnillos();
			int num_puntos=dialog.getPuntosPorAnillo();
			int tipoMalla;
			if (dialog.getTipoMalla()=="Triangulos")
				tipoMalla=0;
			else if (dialog.getTipoMalla()=="Cuadrilateros")
				tipoMalla=1;
			else
				return;
			comando=new GenerarMallaInicial(tipo,archivo,radio,num_anillos,num_puntos,tipoMalla);
			}
		else
			return;

		comando->execute();
		delete this->malla;
		this->malla=comando->getMalla();
		delete comando;

		simpleglscene->clear();
		simpleglscene->updateMalla(malla);

		this->escribirEnLog("Malla generada correctamente.");
		}
	else
		return;

    }

void GUIVentanaPrincipal::on_abrir1_activate(){
        n=1;

  	//Show the dialog and wait for a user response:
  	int result = dialog_abrir->run();

	if (result==Gtk::RESPONSE_OK){
		Gtk::FileFilter* filtro=dialog_abrir->get_filter();
		Comando *comando = NULL;

        bool es_face=false;
		if (filtro->get_name()=="wfm (WFM)"){
		    int tipofiltro=4;
		    es_face=true;
		    list<string> filenames=dialog_abrir->get_filenames();
		    comando = new GenerarMallaInicial(tipofiltro, filenames);
            }
        else if (filtro->get_name()=="wrl (VRML)"){
		    int tipofiltro=5;
		    es_face=true;
		    list<string> filenames=dialog_abrir->get_filenames();
		    comando = new GenerarMallaInicial(tipofiltro, filenames);
            }
		else if (filtro->get_name()=="off (Geomview)"){
			int tipofiltro=0;
			list<string> filenames=dialog_abrir->get_filenames();
			comando = new GenerarMallaInicial(tipofiltro, filenames);
			}
		else if (filtro->get_name()=="txt (Matlab)"){
			int tipofiltro=1;
			list<string> filenames=dialog_abrir->get_filenames();
			GUIDialogAbrirMatlab dialogMatlab;
			dialogMatlab.set_transient_for(*dialog_abrir);
			int resultDialogMatlab=dialogMatlab.run();
			if (resultDialogMatlab==Gtk::RESPONSE_OK){
				int numeroDeAnillos=dialogMatlab.getNumeroDeAnillos();
				int puntosPorAnillo=dialogMatlab.getPuntosPorAnillo();
				string strTipoMalla=dialogMatlab.getTipoMalla();
				int tipoMalla;
				if (strTipoMalla=="Triangulos")
					tipoMalla=0;
				else if (strTipoMalla=="Cuadrilateros")
					tipoMalla=1;
				else
					return;
				comando=new GenerarMallaInicial(tipofiltro,filenames,numeroDeAnillos,puntosPorAnillo,tipoMalla);
				}
			else
				return;
			}
		else if (filtro->get_name()=="txt (nx,ny,nz,u)"){
			int tipofiltro=2;
			list<string> filenames=dialog_abrir->get_filenames();
			if (filenames.size()!=4){
				this->escribirEnLog("Se deben seleccionar 4 archivos para el formato nxnynzu.");
				return;
				}
            filenames.sort();
			comando = new GenerarMallaInicial(tipofiltro, filenames);
			}
		else if (filtro->get_name()=="cms_1 (comsol_1)"){
			int tipofiltro=3;
			list<string> filenames=dialog_abrir->get_filenames();
			comando = new GenerarMallaInicial(tipofiltro, filenames);
			}
		else
			return;

		/*comando->execute();
		delete this->malla;
		this->malla=comando->getMalla();
        delete comando;*/
        this->malla=comando->getMalla();
        dialog_abrir->hide();



    if(es_face){
        //bool exito = this->procesar_malla();//muestra la configuracion de caras

           // if(exito){
                if(malla->tieneTextura()){
                    simpleglscene->setMuestraArcos(false);
                    this->mostrar_arcos1->set_active(false);
             //   }

                simpleglscene->clear();
                simpleglscene->updateMalla(malla, true);

                this->escribirEnLog("Malla cargada correctamente.");
            }else{
                this->escribirEnLog("La malla no se cargó efectivamente");
            }

            }
	}
	else
		simpleglscene->clear();
        simpleglscene->updateMalla(malla, true);
        this->escribirEnLog("Malla cargada correctamente.");

	}


void GUIVentanaPrincipal::on_guardar1_activate(){
	this->on_guardar_como1_activate();
	}

void GUIVentanaPrincipal::on_guardar_como1_activate(){
	if(this->malla == NULL) {
		this->escribirEnLog("La malla aun no esta seteada.");
        return;
    	}

	Gtk::FileChooserDialog dialog("Guardar malla", Gtk::FILE_CHOOSER_ACTION_SAVE);
  	dialog.set_transient_for(*this);

	//Add response buttons the the dialog:
  	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  	dialog.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);

  	//Add filters, so that only certain file types can be selected:
  	Gtk::FileFilter filter_geomview;
  	filter_geomview.set_name("off (Geomview)");
  	filter_geomview.add_pattern("*.off");
  	dialog.add_filter(filter_geomview);

  	Gtk::FileFilter filter_nxnynzu;
  	filter_nxnynzu.set_name("txt (nx,ny,nz,u)");
  	filter_nxnynzu.add_pattern("*.txt");
  	dialog.add_filter(filter_nxnynzu);

	Gtk::FileFilter filter_comsol_1;
  	filter_comsol_1.set_name("cms_1 (comsol_1)");
  	filter_comsol_1.add_pattern("*.cms_1");
  	dialog.add_filter(filter_comsol_1);

	Gtk::FileFilter filter_mll;
  	filter_mll.set_name("mll (Debug)");
  	filter_mll.add_pattern("*.mll");
  	dialog.add_filter(filter_mll);

	int result=dialog.run();

	if (result==Gtk::RESPONSE_OK){
		Gtk::FileFilter* filtro=dialog.get_filter();
		int tipofiltro;
		string filename;
		if (filtro->get_name()=="off (Geomview)"){
			tipofiltro=0;
			filename=dialog.get_filename()+".off";
			}
		else if (filtro->get_name()=="txt (nx,ny,nz,u)"){
			tipofiltro=2;
			filename=dialog.get_filename()+".txt";
			}
		else if (filtro->get_name()=="cms_1 (comsol_1)"){
			tipofiltro=3;
			filename=dialog.get_filename()+".cms_1";
			}
		else if (filtro->get_name()=="mll (Debug)"){
			tipofiltro=4;
			filename=dialog.get_filename()+".mll";
			}
		else
			return;

		Comando* comando = new Guardar(malla, tipofiltro,filename);
		comando->execute();
		delete comando;
		this->escribirEnLog("Malla guardada.");
		}
	else
		return;
	}

void GUIVentanaPrincipal::on_salir1_activate(){
    this->hide();
}

void GUIVentanaPrincipal::on_cortar1_activate() {
}

void GUIVentanaPrincipal::on_copiar1_activate() {
}

void GUIVentanaPrincipal::on_pegar1_activate() {
}

void GUIVentanaPrincipal::on_borrar1_activate(){
	simpleglscene->clear();
	delete malla;
	malla=NULL;
	this->escribirEnLog("Malla borrada.");
	}

void GUIVentanaPrincipal::on_deformar1_activate(){
	if(this->malla == NULL) {
		this->escribirEnLog("La malla aun no esta seteada.");
        return;
    	}
}

void GUIVentanaPrincipal::on_refinar1_activate(){
	if(this->malla == NULL) {
		this->escribirEnLog("La malla aun no esta seteada.");
        return;
    	}

	if(this->malla->getFabricaAlgoritmos()->getAlgoritmosRefinamiento().size() == 0) {
        this->escribirEnLog("No hay algoritmos de refinamiento disponibles para esta malla.");
        return;
    	}

	GUIDialogRefinar dialog;
	int result=dialog.run();

	if (result==Gtk::RESPONSE_APPLY){
		int tipoAlgRefinamiento;
		int tipoCriterio;
		double valorCriterio;

		if (dialog.isLeppDelaunay())
			tipoAlgRefinamiento=0;
		else if (dialog.isDelaunayLongestEdgeBisection())
			tipoAlgRefinamiento=1;
		else
			return;

		if (dialog.isAnguloMinimo()){
			tipoCriterio=0;
			valorCriterio=dialog.anguloMinimo();
			}
		else if (dialog.isAreaCara()){
			tipoCriterio=1;
			valorCriterio=dialog.areaCara();
			}
		else if (dialog.isLargoArcos()){
			tipoCriterio=2;
			valorCriterio=dialog.largoArcos();
			}
		else
			return;

		Comando* comando=new Refinar(malla,tipoAlgRefinamiento,tipoCriterio,valorCriterio);
		comando->execute();
		delete comando;

		simpleglscene->updateMalla(malla, false);

		this->escribirEnLog("Algoritmo refinamiento aplicado.");
		}
	else
		return;
	}

void GUIVentanaPrincipal::on_desrefinar1_activate(){
	if(this->malla == NULL) {
		this->escribirEnLog("La malla aun no esta seteada.");
        return;
    	}

	if(this->malla->getFabricaAlgoritmos()->getAlgoritmosDesrefinamiento().size() == 0) {
        this->escribirEnLog("No hay algoritmos de desrefinamiento disponibles para esta malla.");
        return;
    	}

	GUIDialogDesrefinar dialog;
	int result=dialog.run();

	if (result==Gtk::RESPONSE_APPLY){
		int tipoAlgDesrefinamiento=0;
		int tipoCriterio;
		double valorCriterio;


		if (dialog.isAreaCara()){
			tipoCriterio=1;
			valorCriterio=dialog.areaCara();
			}
		else if (dialog.isLargoArcos()){
			tipoCriterio=2;
			valorCriterio=dialog.largoArcos();
			}
		else
			return;

		Comando* comando=new Desrefinar(malla,tipoAlgDesrefinamiento,tipoCriterio,valorCriterio);
		comando->execute();
		delete comando;

		simpleglscene->updateMalla(malla, false);

		this->escribirEnLog("Algoritmo desrefinamiento aplicado.");
		}
	else
		return;
	}

void GUIVentanaPrincipal::on_mejorar1_activate(){
	if(this->malla == NULL) {
        this->escribirEnLog("La malla aun no esta seteada.");
        return;
    	}

	if(this->malla->getFabricaAlgoritmos()->getAlgoritmosMejoramiento().size() == 0) {
        this->escribirEnLog("No hay algoritmos de mejoramiento disponibles para esta malla.");
        return;
    	}

	Comando *cmd=new Mejorar(malla);
	cmd->execute();
	delete cmd;

	simpleglscene->updateMalla(malla, false);

	this->escribirEnLog("Algoritmo mejoramiento aplicado.");

	}

void GUIVentanaPrincipal::on_triangular1_activate(){
	if(this->malla == NULL) {
        this->escribirEnLog("La malla aun no esta seteada.");
        return;
    	}

	if(this->malla->getTipoMalla() != "quadrilateral") {
        this->escribirEnLog("Error, la malla debe ser de cuadriláteros");
        return;
    	}

	Triangular *cmd=new Triangular((MallaCuadrilateros *)malla);
	cmd->execute();
	Malla *nueva_malla = cmd->getMalla();
	delete cmd;
	delete malla;
	malla = nueva_malla;

	simpleglscene->updateMalla(malla, false);
	cout << "Tipo nueva malla: " << malla->getTipoMalla() << endl;

	this->escribirEnLog("La malla ha sido triangulada.");

	}

void GUIVentanaPrincipal::on_cuadrangular1_activate(){
	if(this->malla == NULL) {
        this->escribirEnLog("La malla aun no esta seteada.");
        return;
    	}

	if(this->malla->getTipoMalla() != "triangular") {
        this->escribirEnLog("Error, la malla debe ser de triángulos");
        return;
    	}

	GUIDialogAlgCentro dialog;
	int result=dialog.run();
	if (result==Gtk::RESPONSE_APPLY){
	    AlgCentroTriangulo *centro = NULL;
        if(dialog.getAlgCentro() == "Baricentro")
            centro = new Baricentro(malla);

        Cuadrangular *cmd=new Cuadrangular((MallaTriangulos *)malla, centro);
        cmd->execute();
        Malla *nueva_malla = cmd->getMalla();
        delete cmd;
        delete malla;
        malla = nueva_malla;

        simpleglscene->updateMalla(malla, false);
        cout << "Tipo nueva malla: " << malla->getTipoMalla() << endl;

        this->escribirEnLog("La malla ha sido cuadrangulada.");
	}
}

void GUIVentanaPrincipal::on_informacion1_activate(){
	if(this->malla == NULL) {
        this->escribirEnLog("La malla aun no esta seteada.");
        return;
    	}

	Informar* informar=new Informar(malla);
	informar->execute();

	GUIDialogInformacion dialog(informar);
	Gtk::Main::run(dialog);

	delete informar;

	}

void GUIVentanaPrincipal::on_mostrar_caras1_activate(){
	simpleglscene->setMuestraCaras(this->mostrar_caras1->get_active());
	}

void GUIVentanaPrincipal::on_mostrar_arcos1_activate(){
	simpleglscene->setMuestraArcos(this->mostrar_arcos1->get_active());
	}

void GUIVentanaPrincipal::on_mostrar_colores_segun_concentracion1_activate(){
	simpleglscene->setMuestraConcentracion(this->mostrar_colores_segun_concentracion1->get_active());
	}

void GUIVentanaPrincipal::on_mostrar_todos_los_frames1_activate(){
    simpleglscene->setMuestraTodosFrames(this->mostrar_todos_los_frames1->get_active());
    }

void GUIVentanaPrincipal::on_enlentecer_animacion1_activate(){
	velocidadAnimacion=velocidadAnimacion+50;
	simpleglscene->pauseAnimacion();
	simpleglscene->startAnimacion(velocidadAnimacion);
	}

void GUIVentanaPrincipal::on_detener_animacion1_activate(){
	simpleglscene->stopAnimacion();
	}

void GUIVentanaPrincipal::on_pausar_animacion1_activate(){
	simpleglscene->pauseAnimacion();
	}

void GUIVentanaPrincipal::on_iniciar_animacion1_activate(){
	simpleglscene->startAnimacion(velocidadAnimacion);
	}

void GUIVentanaPrincipal::on_apurar_animacion1_activate(){
	velocidadAnimacion=velocidadAnimacion-50;
	if (velocidadAnimacion<50)
		velocidadAnimacion=50;
	simpleglscene->pauseAnimacion();
	simpleglscene->startAnimacion(velocidadAnimacion);
	}

void GUIVentanaPrincipal::on_acerca_de1_activate(){
	Gtk::AboutDialog dialog;
	dialog.set_transient_for(*this);
	dialog.set_name("Tree Growth Simulator");
	dialog.set_version("4.0");
	list<string> autores;
	autores.push_back("Renato Valenzuela (Versión 4)");
	autores.push_back("Cristina Melo (Versión 3)");
	autores.push_back("Nicolás Silva (Versión 2)");
	autores.push_back("Ricardo Medina (Version 1)");
	dialog.set_authors(autores);
	dialog.set_comments("Software modelador del crecimiento de arboles usando mallas geometricas.");
	dialog.run();
	}

void GUIVentanaPrincipal::on_toolbuttonNuevo_clicked(){
	this->on_nuevo1_activate();
	}

void GUIVentanaPrincipal::on_toolbuttonAbrir_clicked(){
	this->on_abrir1_activate();
	}

void GUIVentanaPrincipal::on_toolbuttonGuardar_clicked(){
	this->on_guardar1_activate();
	}

void GUIVentanaPrincipal::escribirEnLog(string texto){
	time_t tim=time(NULL);
	tm *time=localtime(&tim);
	int hora=time->tm_hour;
	int minuto=time->tm_min;
	int segundo=time->tm_sec;

	string logviejo=textviewLog->get_buffer()->get_text();

	stringstream stream;
	stream << "[" << hora << ":" << (minuto<10?"0":"") << minuto << ":" << (segundo<10?"0":"") << segundo << "] " << texto << endl << logviejo;

	textviewLog->get_buffer()->set_text(stream.str());
	}

GUIVentanaPrincipal::~GUIVentanaPrincipal(){
	delete simpleglscene;
	delete malla;

	list<Gtk::FileFilter*> filters = dialog_abrir->list_filters();
	for(list<Gtk::FileFilter*>::iterator f = filters.begin(); f != filters.end(); f++ ){
            delete *f;
	}
	delete dialog_abrir;

	}
