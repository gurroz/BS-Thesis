

#ifndef _SIMPLEGLSCENE_HH


#include <iostream>
#include <cstdlib>

#include <gtkmm.h>

#include <gtkglmm.h>

#ifdef G_OS_WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include "malla.h"

#  define _SIMPLEGLSCENE_HH

/*
Clase visualizadora de mallas en OpenGL. Las mallas son seteadas en Display Lists.
La malla principal se setean en el Display List 1. Esto se hace con la funcion updateMalla.
Las mallas de animacion de la secuencia de deforamciones se setean en los Display Lists de
2 en adelante. Se setean con la Funcion updateAnimacion.
*/

class SimpleGLScene : public Gtk::DrawingArea, public Gtk::GL::Widget<SimpleGLScene>
{
public:
        SimpleGLScene();
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
		~SimpleGLScene();

		float diametrox;
		float diametroy;
		float diametroz;

		bool redibujar();
        virtual void drawScene() = 0;
protected:
		float radioCamara;
		float thetaCamara;
		float phiCamara;

		float centrox;
		float centroy;
		float centroz;

		double xVentana;
		double yVentana;

		sigc::connection signalTimeout;

        bool on_expose_event(GdkEventExpose *ev);
        void on_realize();
        bool on_configure_event(GdkEventConfigure *ev);
		bool on_motion_notify_event(GdkEventMotion* event);
		bool on_button_press_event(GdkEventButton* event);

		void copy_scene_values(SimpleGLScene* gl_scene);
};

#endif
