#include "generarmallainicial.h"
#include "generafromoff.h"
#include "generafromarchivosxyzu.h"
#include "generafrommatlab.h"
#include "generafromcomsol_1.h"
#include "generacilindro.h"
#include "generafrommedula.h"
#include "generafromwfm.h"
#include "generafromwrl.h"
#include "interpoladorMixto.h"
#include "interfacemanualregistration.h"


GenerarMallaInicial::GenerarMallaInicial(int tipoFiltro, list<string> filenames, int numeroDeAnillos, int puntosPorAnillo, int tipoMalla):Comando(0){
    algoritmo=NULL;

	if (tipoFiltro==0){
		list<string>::iterator iter=filenames.begin();
		string filename=*iter;
		algoritmo=new GeneraFromOFF(filename);
		assert(algoritmo);
		this->execute();
		}
	else if (tipoFiltro==1){
		list<string>::iterator iter=filenames.begin();
		string filename=*iter;
		algoritmo=new GeneraFromMatLab(filename, numeroDeAnillos, puntosPorAnillo, tipoMalla);
		assert(algoritmo);
		this->execute();
		}
	else if (tipoFiltro==2){
		list<string>::iterator iter=filenames.begin();
		string filename1=*iter;
		iter++;
		string filename2=*iter;
		iter++;
		string filename3=*iter;
		iter++;
		string filename4=*iter;
		algoritmo=new GeneraFromArchivosXYZU(filename1, filename2, filename3, filename4);
		assert(algoritmo);
		this->execute();
		}
	else if (tipoFiltro==3){
		list<string>::iterator iter=filenames.begin();
		string filename=*iter;
		algoritmo=new GeneraFromComsol_1(filename);
		assert(algoritmo);
		this->execute();
		}
    else if (tipoFiltro==4){
        list<string>::iterator iter=filenames.begin();
		string filename=*iter;
		algoritmo=new GeneraFromWFM(filename);
		assert(algoritmo);
		this->execute();
    }
    else if (tipoFiltro==5){
        list<string>::iterator iter=filenames.begin();
		string filename=*iter;
		algoritmo=new GeneraFromWRL(filename);
		assert(algoritmo);
		this->execute();

        RegistrationMethod *registrationMethod = new InterfaceManualRegistration();
        Malla *modelo = GeneraFromWFM("candide.wfm").aplicar();
        this->malla->setMovimientos("candide.wfm");

        bool exito = registrationMethod->execute(this->malla, modelo);

        delete registrationMethod;

        Interpolador *interpolador = new InterpoladorMixto();
        if(exito){
           interpolador->setearInterpolaciones(this->malla, modelo);

        }
    }


	}

GenerarMallaInicial::GenerarMallaInicial (int tipo, int altura, int radio, int numeroDeAnillos, int puntosPorAnillo, int tipoMalla):Comando(0){
	algoritmo=NULL;

	if (tipo==10)
		algoritmo=new GeneraCilindro(altura,radio,numeroDeAnillos,puntosPorAnillo,tipoMalla);

	assert(algoritmo);
		this->execute();
	}

GenerarMallaInicial::GenerarMallaInicial(int tipo, string filename, int radio, int numeroDeAnillos,int puntosPorAnillo, int tipoMalla):Comando(0){
    algoritmo=NULL;

	if (tipo==20)
		algoritmo=new GeneraFromMedula(filename,radio,numeroDeAnillos,puntosPorAnillo,tipoMalla);

	assert(algoritmo);
		this->execute();
    }

void GenerarMallaInicial::execute() {
    this->malla = algoritmo->aplicar();
}

GenerarMallaInicial::~GenerarMallaInicial(){
	delete algoritmo;
	}
