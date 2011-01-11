// generated 2006/7/27 1:06:45 CLT by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to SimpleGLScene.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "SimpleGLScene.hh"
#include "generafromwfm.h"


SimpleGLScene::SimpleGLScene()
{
	this-> xVentana=0;
	this-> yVentana=0;
    this-> thetaCamara = 3 * PI/2;
	this-> phiCamara = PI/2;

	//Eventos para mover el modelo.
	add_events(Gdk::BUTTON1_MOTION_MASK    |
               Gdk::BUTTON3_MOTION_MASK    |
               Gdk::BUTTON_PRESS_MASK      |
               Gdk::BUTTON_RELEASE_MASK    |
               Gdk::VISIBILITY_NOTIFY_MASK);
	signal_motion_notify_event().connect(sigc::mem_fun(*this, &SimpleGLScene::on_motion_notify_event) );
	signal_button_press_event().connect(sigc::mem_fun(*this, &SimpleGLScene::on_button_press_event) );
}

SimpleGLScene::~SimpleGLScene()
{
}

void SimpleGLScene::on_realize()
{
  // We need to call the base on_realize()
  Gtk::DrawingArea::on_realize();

  //
  // Get GL::Window.
  //

  Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();

  //
  // GL calls.
  //

  // *** OpenGL BEGIN ***
  if (!glwindow->gl_begin(get_gl_context()))
    return;

  static GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0};
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_COLOR_MATERIAL);

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClearDepth(1.0);

  glViewport(0, 0, get_width(), get_height());

  /*glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, 1.0, 1.0, 100.0);*/

  /*glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 20.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);*/


  glwindow->gl_end();
  // *** OpenGL END ***
}

bool SimpleGLScene::on_configure_event(GdkEventConfigure* event)
{
  //
  // Get GL::Window.
  //

  Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();

  //
  // GL calls.
  //

  // *** OpenGL BEGIN ***
  if (!glwindow->gl_begin(get_gl_context()))
    return false;

  glViewport(0, 0, get_width(), get_height());

  glwindow->gl_end();
  // *** OpenGL END ***

  return true;
}

bool SimpleGLScene::on_expose_event(GdkEventExpose* event)
{
  //
  // Get GL::Window.
  //

  Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();

  //
  // GL calls.
  //

  // *** OpenGL BEGIN ***
  if (!glwindow->gl_begin(get_gl_context()))
    return false;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 //Fijar parámetros para debugging
/*
	radioCamara = 3.88679;
	thetaCamara = 4.53173;
	phiCamara = 0.90418;
*/

    float camz=centroz+radioCamara*cos(phiCamara);
    float camx=centrox+radioCamara*cos(thetaCamara)*sin(phiCamara);
    float camy=centroy+radioCamara*sin(thetaCamara)*sin(phiCamara);


    glEnable(GL_TEXTURE_2D);

    float aspectRatio=(float)get_width()/get_height();
	float anguloCamara=45.0;
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(anguloCamara, aspectRatio, 0.1, 800);


	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();
  	gluLookAt(camx, camy, camz,
            centrox, centroy, centroz,
            0.0, 0.0, 1.0);

    glTranslatef(0, centroy+centroz, centroz-centroy);
    glRotatef(90, 1.0f, 0.0f, 0.0f);

  	glEnable (GL_POLYGON_OFFSET_FILL); 	//Necesario para permitir dibujar 2 poligonos
    glPolygonOffset (1.0, 1.0); 		//coplanares (Wireframe y poligono solido)

	this->drawScene();

  // Swap buffers.
  if (glwindow->is_double_buffered())
    glwindow->swap_buffers();
  else
    glFlush();

  glwindow->gl_end();
  // *** OpenGL END ***

  return true;
}


bool SimpleGLScene::redibujar()
{
    // force our program to redraw the entire clock.
    Glib::RefPtr<Gdk::Window> win = get_window();
    if (win)
    {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
    return true;
}

void SimpleGLScene::copy_scene_values(SimpleGLScene* gl_scene){
	this->centrox = gl_scene->centrox;
	this->centroy = gl_scene->centroy;
	this->centroz = gl_scene->centroz;
	this->diametrox = gl_scene->diametrox;
	this->diametroy = gl_scene->diametroy;
	this->diametroz = gl_scene->diametroz;
	this->radioCamara = gl_scene->radioCamara;
}

bool SimpleGLScene::on_button_press_event(GdkEventButton* event){
	this->xVentana=event->x;
	this->yVentana=event->y;
	return true;
	}

bool SimpleGLScene::on_motion_notify_event(GdkEventMotion* event){
	if (event->state & GDK_BUTTON3_MASK){
		this->radioCamara=this->radioCamara + (event->y - this->yVentana)/this->get_height()*5*diametroz;
		if (this->radioCamara < 0)
			this->radioCamara=0;
	}
	else if (event->state & GDK_BUTTON1_MASK){
		this->thetaCamara=this->thetaCamara - (event->x - this->xVentana)/this->get_width()*5;
		this->phiCamara=this->phiCamara - (event->y - this->yVentana)/this->get_height()*5;
		if (this->phiCamara >= PI)
			this->phiCamara = PI-0.000001;
		else if (this->phiCamara <= 0)
			this->phiCamara = 0.000001;
	}
    this->xVentana = event->x;
    this->yVentana = event->y;
	this->redibujar();
	return true;
	}
