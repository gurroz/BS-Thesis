
#include "interfacemanualregistration.h"
#include "GUIFaceMatcher.hh"


bool InterfaceManualRegistration::execute(Malla *malla, Malla *modelo){

    GUIFaceMatcher *matchFaces  = new GUIFaceMatcher(malla, modelo);

    Gtk::Main::instance()->run(*matchFaces);

    if(matchFaces->nodos_marcados != NULL){
        int nnodos = modelo->getMaxIndiceNodos() + 1;
        int *nodos_marcados = matchFaces->nodos_marcados;
        malla->asignar_nodos_marcados(nodos_marcados, nnodos);
    }else{
        delete matchFaces;
        return false;
    }
    delete matchFaces;
    return true;

};


