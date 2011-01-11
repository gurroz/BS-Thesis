
#include "GLMainScene.hh"

#include <limits>

///////////////////////////////////////////////////////////////////////////////
//
// OpenGL frame buffer configuration utilities.
//
///////////////////////////////////////////////////////////////////////////////

struct GLConfigUtil
{
  static void print_gl_attrib(const Glib::RefPtr<const Gdk::GL::Config>& glconfig,
                              const char* attrib_str,
                              int attrib,
                              bool is_boolean);

  static void examine_gl_attrib(const Glib::RefPtr<const Gdk::GL::Config>& glconfig);
};

//
// Print a configuration attribute.
//
void GLConfigUtil::print_gl_attrib(const Glib::RefPtr<const Gdk::GL::Config>& glconfig,
                                   const char* attrib_str,
                                   int attrib,
                                   bool is_boolean)
{
  int value;

  if (glconfig->get_attrib(attrib, value))
    {
      std::cout << attrib_str << " = ";
      if (is_boolean)
        std::cout << (value == true ? "true" : "false") << std::endl;
      else
        std::cout << value << std::endl;
    }
  else
    {
      std::cout << "*** Cannot get "
                << attrib_str
                << " attribute value\n";
    }
}

//
// Print configuration attributes.
//
void GLConfigUtil::examine_gl_attrib(const Glib::RefPtr<const Gdk::GL::Config>& glconfig)
{
  std::cout << "\nOpenGL visual configurations :\n\n";

  std::cout << "glconfig->is_rgba() = "
            << (glconfig->is_rgba() ? "true" : "false")
            << std::endl;
  std::cout << "glconfig->is_double_buffered() = "
            << (glconfig->is_double_buffered() ? "true" : "false")
            << std::endl;
  std::cout << "glconfig->is_stereo() = "
            << (glconfig->is_stereo() ? "true" : "false")
            << std::endl;
  std::cout << "glconfig->has_alpha() = "
            << (glconfig->has_alpha() ? "true" : "false")
            << std::endl;
  std::cout << "glconfig->has_depth_buffer() = "
            << (glconfig->has_depth_buffer() ? "true" : "false")
            << std::endl;
  std::cout << "glconfig->has_stencil_buffer() = "
            << (glconfig->has_stencil_buffer() ? "true" : "false")
            << std::endl;
  std::cout << "glconfig->has_accum_buffer() = "
            << (glconfig->has_accum_buffer() ? "true" : "false")
            << std::endl;

  std::cout << std::endl;

  print_gl_attrib(glconfig, "Gdk::GL::USE_GL",           Gdk::GL::USE_GL,           true);
  print_gl_attrib(glconfig, "Gdk::GL::BUFFER_SIZE",      Gdk::GL::BUFFER_SIZE,      false);
  print_gl_attrib(glconfig, "Gdk::GL::LEVEL",            Gdk::GL::LEVEL,            false);
  print_gl_attrib(glconfig, "Gdk::GL::RGBA",             Gdk::GL::RGBA,             true);
  print_gl_attrib(glconfig, "Gdk::GL::DOUBLEBUFFER",     Gdk::GL::DOUBLEBUFFER,     true);
  print_gl_attrib(glconfig, "Gdk::GL::STEREO",           Gdk::GL::STEREO,           true);
  print_gl_attrib(glconfig, "Gdk::GL::AUX_BUFFERS",      Gdk::GL::AUX_BUFFERS,      false);
  print_gl_attrib(glconfig, "Gdk::GL::RED_SIZE",         Gdk::GL::RED_SIZE,         false);
  print_gl_attrib(glconfig, "Gdk::GL::GREEN_SIZE",       Gdk::GL::GREEN_SIZE,       false);
  print_gl_attrib(glconfig, "Gdk::GL::BLUE_SIZE",        Gdk::GL::BLUE_SIZE,        false);
  print_gl_attrib(glconfig, "Gdk::GL::ALPHA_SIZE",       Gdk::GL::ALPHA_SIZE,       false);
  print_gl_attrib(glconfig, "Gdk::GL::DEPTH_SIZE",       Gdk::GL::DEPTH_SIZE,       false);
  print_gl_attrib(glconfig, "Gdk::GL::STENCIL_SIZE",     Gdk::GL::STENCIL_SIZE,     false);
  print_gl_attrib(glconfig, "Gdk::GL::ACCUM_RED_SIZE",   Gdk::GL::ACCUM_RED_SIZE,   false);
  print_gl_attrib(glconfig, "Gdk::GL::ACCUM_GREEN_SIZE", Gdk::GL::ACCUM_GREEN_SIZE, false);
  print_gl_attrib(glconfig, "Gdk::GL::ACCUM_BLUE_SIZE",  Gdk::GL::ACCUM_BLUE_SIZE,  false);
  print_gl_attrib(glconfig, "Gdk::GL::ACCUM_ALPHA_SIZE", Gdk::GL::ACCUM_ALPHA_SIZE, false);

  std::cout << std::endl;
}


GLMainScene::GLMainScene(){
	this->frameActual=1;
    //this->modelo = GeneraFromWFM("candide.wfm").aplicar();
	this->muestraArcos=true;
	this->muestraCaras=true;
	this->muestraConcentracion=true;
	this->muestraNodosDestacados=true;


  //
  // Configure OpenGL-capable visual.
  //

  Glib::RefPtr<Gdk::GL::Config> glconfig;

  // Try double-buffered visual
  glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGB    |
                                     Gdk::GL::MODE_DEPTH  |
                                     Gdk::GL::MODE_DOUBLE);
  if (!glconfig)
    {
      std::cerr << "*** Cannot find the double-buffered visual.\n"
                << "*** Trying single-buffered visual.\n";

      // Try single-buffered visual
      glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGB   |
                                         Gdk::GL::MODE_DEPTH);
      if (!glconfig)
        {
          std::cerr << "*** Cannot find any OpenGL-capable visual.\n";
          std::exit(1);
        }
    }
  // print frame buffer attributes.
  GLConfigUtil::examine_gl_attrib(glconfig);

  //
  // Set OpenGL-capability to the widget.
  //

  set_gl_capability(glconfig);
}

void GLMainScene::drawScene(){
     if(muestraTodosFrames){
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            int nframes=getNumeroDeFrames();
            for (int i=0; i<=nframes; i++){
                if (this->muestraCaras==true)
                    glCallList(i);
                if (this->muestraArcos==true)
                    glCallList(-1*i);
                }
            glDisable(GL_POLYGON_STIPPLE);
            glDisable(GL_BLEND);
            //glCallList(10*frameActual);
        }
        else{
            if (this->muestraCaras==true)
                glCallList(frameActual);

            if (this->muestraArcos==true)
                glCallList(-1*frameActual);
        }
}

void dibujaCuadradoEn(float x, float y, float z, float size=1){
    glBegin(GL_QUADS);

           //glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(x+size,y+size,z-size);	// Top Right Of The Quad (Top)
    glVertex3f(x-size,y+size,z-size);	// Top Left Of The Quad (Top)
    glVertex3f(x-size,y+size,z+size);	// Bottom Left Of The Quad (Top)
    glVertex3f(x+size,y+size,z+size);	// Bottom Right Of The Quad (Top)

    glVertex3f(x+size,y-size,z+size);	// Top Right Of The Quad (Bottom)
    glVertex3f(x-size,y-size,z+size);	// Top Left Of The Quad (Bottom)
    glVertex3f(x-size,y-size,z-size);	// Bottom Left Of The Quad (Bottom)
    glVertex3f(x+size,y-size,z-size);	// Bottom Right Of The Quad (Bottom)

    glVertex3f(x+size,y+size,z+size);	// Top Right Of The Quad (Front)
    glVertex3f(x-size,y+size,z+size);	// Top Left Of The Quad (Front)
    glVertex3f(x-size,y-size,z+size);	// Bottom Left Of The Quad (Front)
    glVertex3f(x+size,y-size,z+size);	// Bottom Right Of The Quad (Front)

    glVertex3f(x+size,y-size,z-size);	// Top Right Of The Quad (Back)
    glVertex3f(x-size,y-size,z-size);	// Top Left Of The Quad (Back)
    glVertex3f(x-size,y+size,z-size);	// Bottom Left Of The Quad (Back)
    glVertex3f(x+size,y+size,z-size);	// Bottom Right Of The Quad (Back)

    glVertex3f(x-size,y+size,z+size);	// Top Right Of The Quad (Left)
    glVertex3f(x-size,y+size,z-size);	// Top Left Of The Quad (Left)
    glVertex3f(x-size,y-size,z-size);	// Bottom Left Of The Quad (Left)
    glVertex3f(x-size,y-size,z+size);	// Bottom Right Of The Quad (Left)

    glVertex3f(x+size,y+size,z-size);	// Top Right Of The Quad (Right)
    glVertex3f(x+size,y+size,z+size);	// Top Left Of The Quad (Right)
    glVertex3f(x+size,y-size,z+size);	// Bottom Left Of The Quad (Right)
    glVertex3f(x+size,y-size,z-size);
    glEnd();
}


void GLMainScene::updateMalla(Malla* malla, bool updatePosCamara){
	assert(malla);
	Malla *main_malla = malla;

  // Get GL::Window.
  Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();
  // GL calls.
  // *** OpenGL BEGIN ***
  if (!glwindow->gl_begin(get_gl_context()))
    return;


	vector<int>* nodosADestacar;
	if (muestraNodosDestacados && malla->getNodosDestacados()->size()>0)
		nodosADestacar=malla->getNodosDestacados();
	else
		nodosADestacar=NULL;

	float minx=numeric_limits<float>::max();
	float miny=numeric_limits<float>::max();
	float minz=numeric_limits<float>::max();
	float maxx=-1*numeric_limits<float>::max();
	float maxy=-1*numeric_limits<float>::max();
	float maxz=-1*numeric_limits<float>::max();

  	Cara* c;
  	Nodo* n;

  	vector<int> ind_arcos;
  	vector<int> ind_nodos;

  	int indiceListaGL=1;

	glNewList(indiceListaGL, GL_COMPILE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for(;malla!= NULL; malla = malla->nextMalla()){     /** LEER TODAS LAS SUBMALLAS DE LA MALLA (ojos)**/

	if(malla->tieneTextura()){
        glBindTexture(GL_TEXTURE_2D, malla->getTextura());   // 2d texture (x and y size)
	}

	for (int i=0; i<= malla->getMaxIndiceCaras(); i++){
		c=malla->getCara(i);
		if (c!=NULL){
			ind_nodos=c->getNodos();
			glBegin(GL_POLYGON);
				for (int j=0; j<(int)ind_nodos.size(); j++){

					n=malla->getNodo(ind_nodos[j]);
					float x=n->getPunto().getX();
					float y=n->getPunto().getY();
					float z=n->getPunto().getZ();
					if (x>maxx) maxx=x;
					if (y>maxy) maxy=y;
					if (z>maxz) maxz=z;
					if (x<minx) minx=x;
					if (y<miny) miny=y;
					if (z<minz) minz=z;

                    if(malla->tieneTextura()){
                        glColor3f(1.0f, 1.0f, 1.0f);
                        glTexCoord2f(n->getTextureX(), n->getTextureY());
                    }else{
                       if(muestraConcentracion) {
                            double max = malla->getConcentracionMax() == 0 ? 1: malla->getConcentracionMax();
                            glColor4f(0.0,n->getConcentracion()/max,1.0-n->getConcentracion()/max,0.5);
                        }
                        else if(nodosADestacar!=NULL && find(nodosADestacar->begin(),nodosADestacar->end(),ind_nodos[j])!=nodosADestacar->end()) {
                            glColor3f(0.0,0.0,1.0);
                        }
                        else {
                            glColor3f(1.0,1.0,1.0);
                        }
                    }

					glNormal3f(n->getNormal().getPunto().getX(),n->getNormal().getPunto().getY(),n->getNormal().getPunto().getZ());


					glVertex3f(x,y,z);

					}
  			glEnd();
			}
		}
    } /** FIN LEER TODAS LAS MALLAS **/


    malla = main_malla; //volver a la malla original
  	glEndList();

	//Ahora hago la list del wireframe
    glNewList((unsigned int)-1*indiceListaGL, GL_COMPILE);

	for(;malla!= NULL; malla = malla->nextMalla()){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glPolygonMode(GL_BACK, GL_NONE);
        glColor3f(0.0,0.0,0.0);         //DIBUJA WIREFRAME DE MALLA
        for (int i=0; i<= malla->getMaxIndiceCaras(); i++){
            c=malla->getCara(i);
            if (c!=NULL){
                ind_nodos=c->getNodos();
                glBegin(GL_POLYGON);
                    for (int j=0; j<(int)ind_nodos.size(); j++){
                        n=malla->getNodo(ind_nodos[j]);
                        float x=n->getPunto().getX();
                        float y=n->getPunto().getY();
                        float z=n->getPunto().getZ();
                        glNormal3f(n->getNormal().getPunto().getX(),n->getNormal().getPunto().getY(),n->getNormal().getPunto().getZ());
                        glVertex3f(x,y,z);
                    }
                glEnd();
            }
        }
	}
  	glEndList();

	if (updatePosCamara){

	    this->centrox=(minx+maxx)/2;
        this->centroy=(miny+maxy)/2;
        this->centroz=(minz+maxz)/2;

        this->diametrox=maxx-minx;
        this->diametroy=maxy-miny;
        this->diametroz=maxz-minz;

        float diam=diametrox;
        if (diametroy>diam)
            diam=diametroy;
        if (diametroz>diam)
            diam=diametroz;

        float zNear = 1.0;
        float zFar = zNear+(4*diam);
        float aspectRatio=(float)get_width()/get_height();
        float anguloCamara=45.0;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(anguloCamara, aspectRatio, 0.1*zNear, zFar);


		this->radioCamara=2*diam;
		this->thetaCamara=3 * PI/2;
		this->phiCamara= PI/2;
		}

    //frameActual=getNumeroDeFrames();
    frameActual = 1;

   // *** OpenGL END ***
   glwindow->gl_end();

	this->redibujar();
	}


void GLMainScene::updateAnimacion(int frame, Malla* malla){
	assert(frame>=1 && malla!=NULL);
	Malla *main_malla = malla;

    // Get GL::Window.
    Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();
    // GL calls.
    // *** OpenGL BEGIN ***
    if (!glwindow->gl_begin(get_gl_context()))
    return;


	vector<int>* nodosADestacar;
	if (muestraNodosDestacados && malla->getNodosDestacados()->size()>0)
		nodosADestacar=malla->getNodosDestacados();
	else
		nodosADestacar=NULL;

	vector<int> ind_nodos;

  	Cara* c;
  	Nodo* n;

	glNewList(frame, GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0.0,1.0,0.0);
	for(;malla!= NULL; malla = malla->nextMalla()){     /** LEER SUBMALLAS **/

    if(malla->tieneTextura()){
        glBindTexture(GL_TEXTURE_2D, malla->getTextura());   // 2d texture (x and y size)
	}
	for (int i=0; i<= malla->getMaxIndiceCaras(); i++){
		c=malla->getCara(i);
		if (c!=NULL){
			ind_nodos=c->getNodos();
			glBegin(GL_POLYGON);
				for (int j=0; j<(int)ind_nodos.size(); j++){
					n=malla->getNodo(ind_nodos[j]);
					float x=n->getPunto().getX();
					float y=n->getPunto().getY();
					float z=n->getPunto().getZ();
					 if(malla->tieneTextura()){
                        glColor3f(1.0f, 1.0f, 1.0f);
                        glTexCoord2f(n->getTextureX(), n->getTextureY());
                    }else{
                        if(muestraConcentracion)
                            glColor3f(0.0,n->getConcentracion()/malla->getConcentracionMax(),1.0-n->getConcentracion()/malla->getConcentracionMax());
                        else if(nodosADestacar!=NULL && find(nodosADestacar->begin(),nodosADestacar->end(),ind_nodos[j])!=nodosADestacar->end())
                            glColor3f(0.0,0.0,1.0);
                        else
                            glColor3f(0.0,1.0,0.0);
                    }
					glNormal3f(n->getNormal().getPunto().getX(),n->getNormal().getPunto().getY(),n->getNormal().getPunto().getZ());
					glVertex3f(x,y,z);
					}
  			glEnd();
			}
		}
	} /** FIN LEER TODAS LAS MALLAS */

  	glEndList();
	malla = main_malla;


	//Ahora hago la list del wireframe
	glNewList(-1*frame, GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1.0,0.0,0.0);
	for (int i=0; i<= malla->getMaxIndiceCaras(); i++){
		c=malla->getCara(i);
		if (c!=NULL){
			ind_nodos=c->getNodos();
			glBegin(GL_POLYGON);
				for (int j=0; j<(int)ind_nodos.size(); j++){
					n=malla->getNodo(ind_nodos[j]);
					float x=n->getPunto().getX();
					float y=n->getPunto().getY();
					float z=n->getPunto().getZ();
					glNormal3f(n->getNormal().getPunto().getX(),n->getNormal().getPunto().getY(),n->getNormal().getPunto().getZ());
					glVertex3f(x,y,z);
					}
  			glEnd();
			}
		}
  	glEndList();

    // *** OpenGL END ***
    glwindow->gl_end();
}

void GLMainScene::startAnimacion(int milisegundos){
	signalTimeout= Glib::signal_timeout().connect(sigc::mem_fun(*this, &GLMainScene::updateFrame), milisegundos);
	}

void GLMainScene::stopAnimacion(){
	signalTimeout.disconnect();
	frameActual=1;//getNumeroDeFrames();
	this->redibujar();
	}

void GLMainScene::pauseAnimacion(){
	signalTimeout.disconnect();
	}

bool GLMainScene::updateFrame(){
	frameActual++;
	if (!glIsList(frameActual))
		frameActual=1;
	this->redibujar();
	return true;
	}

int GLMainScene::getNumeroDeFrames(){
    int i=1;
    while(glIsList(i))
        i++;
    return i-1;
    }

void GLMainScene::setMuestraArcos(bool valor){
	this->muestraArcos=valor;
	this->redibujar();
	}
void GLMainScene::setMuestraCaras(bool valor){
	this->muestraCaras=valor;
	this->redibujar();
	}
void GLMainScene::setMuestraConcentracion(bool valor){
	this->muestraConcentracion=valor;
	}
void GLMainScene::setMuestraTodosFrames(bool valor){
    this->muestraTodosFrames=valor;
    this->redibujar();
    }

void GLMainScene::clear(){
	int frame=1;
	while (true){
		glDeleteLists(frame,1);
		frame++;
		if (!glIsList(frame))
			break;
		}
	this->redibujar();
	}

GLMainScene::~GLMainScene(){

}
