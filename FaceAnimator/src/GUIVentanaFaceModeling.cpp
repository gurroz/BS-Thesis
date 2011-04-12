/**
 @author Renato Valenzuela Palominos
 */

#include "GUIVentanaFaceModeling.hh"
#if GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
//#include <sigc++/compatibility.h>
#define GMM_GTKMM_22_24(a,b) b
#else //gtkmm 2.2
#define GMM_GTKMM_22_24(a,b) a
#endif //


#include "generafromwfm.h"
#include <fstream>


 GUIVentanaFaceModeling::GUIVentanaFaceModeling(): GUIVentanaPrincipal("Face Animator"){
    win_auv = new GUI_AUVSelector(this);

    menuitem3_menu->items().push_front(Gtk::Menu_Helpers::CheckMenuElem("Mostrar ventana con Action Units"));
    mostrar_auv1 = (Gtk::CheckMenuItem *)&menuitem3_menu->items().front();
    mostrar_auv1->set_active(false);
    mostrar_auv1->signal_activate().connect(sigc::mem_fun(*this, &GUIVentanaFaceModeling::on_mostrar_auv1_activate), false);

    //interpolador = new InterpoladorUno();
//    interpolador = new InterpoladorMixto();
    value_ant = NULL;

 };

 void GUIVentanaFaceModeling::moverMallaAUV(int i, double value){
     if(this->malla != NULL){
         this->malla->moverNodosSegunParametro(i, value*simpleglscene->diametrox);
         this->simpleglscene->updateMalla(malla, false);
     }
 };

 void GUIVentanaFaceModeling::moverShapeUnit(int i, double value){
     if(this->malla != NULL){
         this->malla->moverNodosSegunShapeUnit(i, value);
         this->simpleglscene->updateMalla(malla, false);
     }
 };

void GUIVentanaFaceModeling::on_mostrar_auv1_activate(){
    if(this->mostrar_auv1->get_active()){
        win_auv->show();
    }else{
        win_auv->hide();
    }
}

 GUIVentanaFaceModeling::~GUIVentanaFaceModeling(){
    delete win_auv;
    if(value_ant != NULL){
        delete[] value_ant;
    }
 };


 void GUIVentanaFaceModeling::on_abrir1_activate(){
    win_auv->hide();
    GUIVentanaPrincipal::on_abrir1_activate();
    win_auv->reset();
 };

 bool GUIVentanaFaceModeling::procesar_malla(){

/*    RegistrationMethod *registrationMethod = new InterfaceManualRegistration();
    Malla *modelo = GeneraFromWFM("candide.wfm").aplicar();
    this->malla->setMovimientos("candide.wfm");

    bool exito = registrationMethod->execute(this->malla, modelo);

    delete registrationMethod;

    if(exito){
        interpolador->setearInterpolaciones(this->malla, modelo);
        return true;
    }
    */
    return false;

};

void GUIVentanaFaceModeling::on_deformar1_activate(){
   if(this->malla == NULL) {
		this->escribirEnLog("La malla aun no esta seteada.");
        return;
    }

    Gtk::FileChooserDialog* dialog = new Gtk::FileChooserDialog("Abrir archivo de movimientos", Gtk::FILE_CHOOSER_ACTION_OPEN);
  	dialog->set_transient_for(*this);
	dialog->set_select_multiple(false);

  	//Add response buttons the the dialog:
  	dialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  	dialog->add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

  	//Add filters, so that only certain file types can be selected:

  	Gtk::FileFilter* filter_cd3 = new Gtk::FileFilter();
  	filter_cd3->set_name("Archivo .cd3 (Candide-3)");
  	filter_cd3->add_pattern("*.cd3");
  	dialog->add_filter(*filter_cd3);

  	Gtk::FileFilter* filter_fap = new Gtk::FileFilter();
  	filter_fap->set_name("Archivo .fap (MPEG-4)");
  	filter_fap->add_pattern("*.fap");
  	dialog->add_filter(*filter_fap);

  	int result = dialog->run();

  	if (result==Gtk::RESPONSE_OK){
        simpleglscene->stopAnimacion();
        string filename = dialog->get_filename();
        moveFromFile(filename);
  	}
  	dialog->hide();
    delete dialog;
    simpleglscene->redibujar();

};

void GUIVentanaFaceModeling::moveFromFile(string name){
    ifstream in(name.c_str());
    if(in){
        int NUMBER = (name.find(".fap") != string::npos? 68 : 14);

        char line[256];

        in.getline(line, 256);
        stringstream streamin(line);
        string version;
        string nombre;
        int FPS;
        int NF;
        streamin >> version;
        streamin >> nombre;
        streamin >> FPS;
        streamin >> NF;

        velocidadAnimacion = 1000/FPS;

        static bool first_time = true;
        if(first_time){
            value_ant = new double[NUMBER];
            for(int i = 0; i < NUMBER; ++i){
                value_ant[i] = 0;
            }
            first_time = false;
        }

        simpleglscene->clear();
        simpleglscene->updateMalla(malla, false);



        for(int i = 0; i < NF; ++i){
            in.getline(line, 256);
            if (in.fail()){
                break;
            }
            stringstream line_pars(line);
            bool used[NUMBER];
            int count = 0;
            for(int j = 0; j< NUMBER; ++j){
                int on_off;
                line_pars >> on_off;
                if(on_off == 1){
                    used[j] = true;
                    count++;
                }
                else
                    used[j] = false;
            }


            in.getline(line, 256);
            if (in.fail()){
                break;
            }
            stringstream line_frame(line);

            int frame;
            line_frame >> frame;

            for(int j = 0; j< NUMBER; ++j){
                if(used[j]){
                    double quantity;
                    line_frame >> quantity;
                    this->malla->moverNodosSegunParametro(j, (quantity-value_ant[j])*simpleglscene->diametrox/150.0);
                    value_ant[j] = quantity;
                }
            }
            this->simpleglscene->updateAnimacion(i+1, malla);
        }
    }
};

 void GUIVentanaFaceModeling::closedAUV(){
    mostrar_auv1->set_active(false);
 };
