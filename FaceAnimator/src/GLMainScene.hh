
#ifndef _SIMPLEGLSCENEPARAMALLAS_HH


#  define _SIMPLEGLSCENEPARAMALLAS_HH

#include "SimpleGLScene.hh"

class GLMainScene: public SimpleGLScene{
public:
        GLMainScene();
		void updateMalla(Malla* malla, bool updatePosCamara=true);	//Setea el Display List principal por la malla dada. updatePosCamera (opcional) indica si se debe reajustar la camara.
		void updateAnimacion(int frame, Malla* malla); //Setea los Display Lists de animacion. Frame parte del 2. El 1 esta seteado por updateMalla.
		void startAnimacion(int milisegundos);	//Comienza la animacion con milisegundos entre cada frame.
		void pauseAnimacion();
		void stopAnimacion();	//Detiene la animacion.
		void setMuestraArcos(bool valor);	//Muestra arcos de las mallas.
		void setMuestraCaras(bool valor);	//Muestra caras de las mallas.
		void setMuestraConcentracion(bool valor);
		void setMuestraTodosFrames(bool valor);
		void clear();	//Borra los Display Lists de la malla principal y las animaciones.
		~GLMainScene();

		//float diametrox;
		//float diametroy;
		//float diametroz;
protected:
        void drawScene();
        int getNumeroDeFrames();
		int frameActual;
        Malla * modelo;
        bool updateFrame();

		bool muestraCaras;
		bool muestraArcos;
		bool muestraConcentracion;
		bool muestraNodosDestacados;
		bool muestraTodosFrames;
};



#endif
