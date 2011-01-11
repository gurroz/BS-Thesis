// generated 2009/5/21 18:32:37 CLT by rvalenzu@rvalenzu-laptop.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to GUIVentanaPrincipal.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "GUIFaceMatcher.hh"
#include "SimpleGLScenePrimario.hh"
#include "SimpleGLSceneSecundario.hh"
#include <fstream>
#include <map>
#include <limits>

GUIFaceMatcher::GUIFaceMatcher(Malla * m, Malla *modelo){
    this->malla = m;
    this->nodos_marcados = NULL;

    drawingArea1 = new SimpleGLScenePrimario(malla, modelo);
    hboxDrawings->pack1(*drawingArea1);
    drawingArea1->show();

	scale_y->set_value(drawingArea1->transy);
	scale_z->set_value(drawingArea1->transz);

    drawingArea2 = new SimpleGLSceneSecundario(drawingArea1);
    hboxDrawings->pack2(*drawingArea2);
	drawingArea2->show();


    parameters->signal_value_changed_connect(this, &GUIFaceMatcher::parameter_change);
    //parameters2->signal_value_changed_connect(this, &GUIFaceMatcher::parameter_change2);

    vscale_zoom->signal_value_changed().connect( sigc::mem_fun(*this, &GUIFaceMatcher::zoom), false);
    scale_x->signal_value_changed().connect(sigc::mem_fun(*this, &GUIFaceMatcher::change_pos), false);
    scale_y->signal_value_changed().connect(sigc::mem_fun(*this, &GUIFaceMatcher::change_pos), false);
    scale_z->signal_value_changed().connect(sigc::mem_fun(*this, &GUIFaceMatcher::change_pos), false);

    scale_rotx->signal_value_changed().connect(sigc::mem_fun(*this, &GUIFaceMatcher::change_angle), false);
    scale_roty->signal_value_changed().connect(sigc::mem_fun(*this, &GUIFaceMatcher::change_angle), false);
    scale_rotz->signal_value_changed().connect(sigc::mem_fun(*this, &GUIFaceMatcher::change_angle), false);
    //this->signal_hide().connect(sigc::mem_fun(*this, &GUIFaceMatcher::on_cerrar), false);

    //cargarVariables();
}

bool GUIFaceMatcher::on_delete_event(GdkEventAny * 	event){
       on_quit1_activate();
       return true;
}

void GUIFaceMatcher::guardarVariables(string file){
    ofstream out(file.c_str());
    stringstream st;

    double zoom = vscale_zoom->get_value();
    st << "zoom" << " " << zoom << endl;
    st << "factor_inicial" << " " << drawingArea1->get_factor_inicial() << endl;
    out.write(st.str().c_str(), st.str().length());
    st.str("");

    double trans_x = scale_x->get_value();
    double trans_y = scale_y->get_value();
    double trans_z = scale_z->get_value();
    st << "trans_x" << " " << trans_x << endl;
    st << "trans_y" << " " << trans_y << endl;
    st << "trans_z" << " " << trans_z << endl;
    out.write(st.str().c_str(), st.str().length());
    st.str("");

    double rot_x = scale_rotx->get_value();
    double rot_y = scale_roty->get_value();
    double rot_z = scale_rotz->get_value();
    st << "rot_x" << " " << rot_x << endl;
    st << "rot_y" << " " << rot_y << endl;
    st << "rot_z" << " " << rot_z << endl;
    out.write(st.str().c_str(), st.str().length());
    st.str("");

    int N = 15;
    st << "n_param" << " " << N << endl;
    out.write(st.str().c_str(), st.str().length());
    st.str("");

    for(int i = 0; i< N; ++i){
        double p = parameters->get_value(i);
        st << "param_" << i << " " << p << endl;
    }
    out.write(st.str().c_str(), st.str().length());

}

void GUIFaceMatcher::cargarVariables(string name){

    ifstream in(name.c_str());
    if(in){
        char line[256];

        std::map<std::string, double> valores;
        for(int i = 0; true; ++i){
            in.getline(line, 256);
            if (in.fail()){
                break;
            }
            stringstream streamin(line);
            string name;
            streamin >> name;
            double value;
            streamin >> value;
            valores[name] = value;
        }

        in.close();


        double zoom = valores["zoom"];
        vscale_zoom->set_value(zoom);
        drawingArea1->set_zoom(zoom);

        double trans_x = valores["trans_x"];
        double trans_y = valores["trans_y"];
        double trans_z = valores["trans_z"];
        scale_x->set_value(trans_x);
        scale_y->set_value(trans_y);
        scale_z->set_value(trans_z);
        drawingArea1->set_translation(trans_x, trans_y, trans_z);

        double rot_x = valores["rot_x"];
        double rot_y = valores["rot_y"];
        double rot_z = valores["rot_z"];
        scale_rotx->set_value(rot_x);
        scale_roty->set_value(rot_y);
        scale_rotz->set_value(rot_z);
        drawingArea1->set_rotation(rot_x, rot_y, rot_z);

        double n_param = valores["n_param"];
        stringstream param_("param_");
        for (int i = 0; i<n_param; ++i){
            stringstream param_;
            param_ << "param_" << i;
            double val = valores[ param_.str() ];
            parameters->set_value(i, val);
        }
    }
}


void GUIFaceMatcher::fill_nodos_marcados(){
    Malla* modelo = drawingArea1->get_malla_modelo();
    int N = modelo->getMaxIndiceNodos();

    //guardarVariables();
    nodos_marcados = new int[N+1];

    double dist[N+1];

    double mmm = numeric_limits<double>::max();
    for(int j=0; j<= N; j++){
        dist[j] = mmm;              //distancia mínima al elementos j del modelo
    }
    Nodo *nj_modelo;
    Nodo *ni;
    Nodo *nk;

    std::map<int, int> usados;          //<nodo_malla, nodo_cercano en modelo>
    for (int j_modelo=0; j_modelo<= N; j_modelo++){
        nj_modelo = modelo->getNodo(j_modelo);
        for (int i=0; i<= malla->getMaxIndiceNodos(); i++){
            ni = malla->getNodo(i);
             double d = ni->distancia(nj_modelo);
            if( d < dist[j_modelo] ){
                std::map<int,int>::iterator ff = usados.find(i);     //encontrar si ya usé el nodo i
                if(ff != usados.end()){     //si es que ya lo usé para otro
                    int otro_int_modelo = ff->second;      //El otro nodo del modelo que está cerca de este nodo de la malla.
                    if(d < dist[otro_int_modelo]){             //si este está más cerca que el otro
                                                                //cambio el cercano del otro (otro_int_modelo)
                        dist[otro_int_modelo] = numeric_limits<double>::max();
                        ////cambiar nodo cercano de otro_int
                        for (int iii=0; iii<= malla->getMaxIndiceNodos(); iii++){
                            if(usados.find(iii) != usados.end()) continue;      //si el nuevo nodo también ya lo usé.

                            double dist_ies = malla->getNodo(iii)->distancia(modelo->getNodo(otro_int_modelo));
                            if( dist_ies < dist[otro_int_modelo] ){
                                dist[otro_int_modelo] = dist_ies;
                                nodos_marcados[otro_int_modelo] = iii;
                            }
                        }
                        usados[nodos_marcados[otro_int_modelo]] = otro_int_modelo;
                        ////-
                    }else{
                        continue;   //si es que el otro está más cerca de j, continuo sin hacer nada con este i.
                    }
                }
                dist[j_modelo] = d;
                nodos_marcados[j_modelo] = i;
            }
        }
        usados[nodos_marcados[j_modelo]] = j_modelo;
    }

}

Malla *GUIFaceMatcher::getModelo(){
        return drawingArea1->get_malla_modelo();
}

void GUIFaceMatcher::parameter_change(int i){
    double val = parameters->get_dif(i);
    if(i == 14)
        drawingArea1->changed2(10, val);
    else
        drawingArea1->changed(i, val);
    drawingArea1->redibujar();
    drawingArea2->redibujar();
}

void GUIFaceMatcher::parameter_change2(int i){

}


void GUIFaceMatcher::zoom(){
    double val = vscale_zoom->get_value();
    drawingArea1->set_zoom(val);
    drawingArea1->redibujar();
    drawingArea2->redibujar();
}

void GUIFaceMatcher::change_pos(){
    float x = scale_x->get_value();
    float y = scale_y->get_value();
    float z = scale_z->get_value();
    drawingArea1->set_translation(x, y, z);
    drawingArea1->redibujar();
    drawingArea2->redibujar();
}

void GUIFaceMatcher::change_angle(){
    float x = scale_rotx->get_value();
    float y = scale_roty->get_value();
    float z = scale_rotz->get_value();
    drawingArea1->set_rotation(x, y, z);
    drawingArea1->redibujar();
    drawingArea2->redibujar();
}

void GUIFaceMatcher::on_open_configuration1_activate()
{
    Gtk::FileChooserDialog* dialog = new Gtk::FileChooserDialog("Abrir configuración de parámetros", Gtk::FILE_CHOOSER_ACTION_OPEN);
  	dialog->set_transient_for(*this);
	dialog->set_select_multiple(false);

  	//Add response buttons the the dialog:
  	dialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  	dialog->add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

  	//Add filters, so that only certain file types can be selected:
  	Gtk::FileFilter* filter = new Gtk::FileFilter();
  	filter->set_name("Archivo de Configuración (.conf)");
  	filter->add_pattern("*.conf");
  	dialog->add_filter(*filter);

  	int result = dialog->run();

  	if (result==Gtk::RESPONSE_OK){
        string filename=dialog->get_filename();
        cargarVariables(filename);
  	}
  	dialog->hide();
  	delete dialog;

    drawingArea1->redibujar();
    drawingArea2->redibujar();
}

void GUIFaceMatcher::on_save_configuration1_activate()
{
    // ELEGIR ARCHIVO
    Gtk::FileChooserDialog dialog("Guardar configuración de parámetros", Gtk::FILE_CHOOSER_ACTION_SAVE);
  	dialog.set_transient_for(*this);

	//Add response buttons the the dialog:
  	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  	dialog.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);

  	//Add filters, so that only certain file types can be selected:
  	Gtk::FileFilter* filter = new Gtk::FileFilter();
  	filter->set_name("Archivo de Configuración (.conf)");
  	filter->add_pattern("*.conf");
  	dialog.add_filter(*filter);

	int result=dialog.run();

	if (result==Gtk::RESPONSE_OK){
        string filename = dialog.get_filename();
        guardarVariables(filename);
	}
	dialog.hide();
}

void GUIFaceMatcher::on_ok1_activate()
{
    fill_nodos_marcados();
    this->hide();
}

void GUIFaceMatcher::on_quit1_activate()
{
    this->hide();
}

GUIFaceMatcher::~GUIFaceMatcher(){
    delete drawingArea1;
    delete drawingArea2;
    if(nodos_marcados != NULL)
        delete[] nodos_marcados;
}
