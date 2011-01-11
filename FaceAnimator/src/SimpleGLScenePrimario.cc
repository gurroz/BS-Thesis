// generated 2006/7/27 1:06:45 CLT by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to SimpleGLScene.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "SimpleGLScenePrimario.hh"

SimpleGLScenePrimario::SimpleGLScenePrimario(Malla *m, Malla *mod) : SimpleGLScene()
{
	this->malla = m;
	this->modelo = mod;
    this->times = 0;

	int list_actual = 1;
    while(glIsList(list_actual))
        ++list_actual;
	zoom = 1;
	angle_x = 0;
	angle_y = 0;
	angle_z = 0;

	Nodos *nnn = malla->getNodos();
    double maxx = nnn->get_maxx();
    double minx = nnn->get_minx();
    double maxy = nnn->get_maxy();
    double miny = nnn->get_miny();
    double maxz = nnn->get_maxz();
    double minz = nnn->get_minz();

    centrox = (maxx + minx)/2;
    centroy = (maxy + miny)/2;
    centroz = (maxz + minz)/2;

    diametrox=maxx-minx;
	diametroy=maxy-miny;
	diametroz=maxz-minz;

    diam = diametrox;
    if(diametroy > diam)
        diam = diametroy;
    if(diametroz > diam)
        diam = diametroz;
    radioCamara = 1.8*diam;

    double may = modelo->getNodos()->get_maxy();
    double miy = modelo->getNodos()->get_miny();
    double maz = modelo->getNodos()->get_maxz();
    double miz = modelo->getNodos()->get_minz();
    double max = modelo->getNodos()->get_maxx();
    double mix = modelo->getNodos()->get_minx();


    double factor = (maxy - miny)/(may - miy);
    //double translatez = (maxz + minz - maz - miz)/2;
    double translatez = maxz - maz*factor;
    double translatey = maxy - may*factor;
    double translatex = maxx - max*factor;

    Nodo *n;
    for (int i=0; i<= modelo->getMaxIndiceNodos(); i++){
       n = modelo->getNodo(i);
       double x = n->getPunto().getX();
       double y = n->getPunto().getY();
       double z = n->getPunto().getZ();
       n->setPunto(Punto(x*factor, y*factor, z*factor));
    }
    factor_inicial = factor;

    transy = translatez/diam*10;
    transz = translatey/diam*10;
    transx = 0;


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

  //
  // Set OpenGL-capability to the widget.
  //

  set_gl_capability(glconfig);

}

SimpleGLScenePrimario::~SimpleGLScenePrimario()
{
}

double SimpleGLScenePrimario::get_factor_inicial(){
    return factor_inicial;
}

void SimpleGLScenePrimario::on_realize(){
    SimpleGLScene::on_realize();

    inner_list = 1;
    while( glIsList(inner_list) ){
        ++inner_list;
    }

    list_number = inner_list + 1;
    while( glIsList(list_number) ){
        ++list_number;
    }
    Cara *c;
    Nodo* n;
    vector<int> ind_nodos;

    redo_model_list();

    glNewList(list_number, GL_COMPILE);
	if(malla->tieneTextura()){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, malla->getTextura());   // 2d texture (x and y size)
	}

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
	for (int i=0; i<= malla->getMaxIndiceCaras(); i++){
		c=malla->getCara(i);
		if (c!=NULL){
			ind_nodos=c->getNodos();
			glBegin(GL_TRIANGLES);
            for (int j=0; j<(int)ind_nodos.size(); j++){
                n=malla->getNodo(ind_nodos[j]);
                float x=n->getPunto().getX();
                float y=n->getPunto().getY();
                float z=n->getPunto().getZ();

                if(malla->tieneTextura()){
                    glColor3f(0.5f, 0.8f, 0.9f);
                    glTexCoord2f(n->getTextureX(), n->getTextureY());
                }else{
                    glColor3f(0.0,1.0,0.0);
                }
                glNormal3f(n->getNormal().getPunto().getX(),n->getNormal().getPunto().getY(),n->getNormal().getPunto().getZ());

                glVertex3f(x,y,z);
            }
  			glEnd();
		}
    }
    glDisable(GL_CULL_FACE);
    //glCallList(inner_list);
	glEndList();
}

void SimpleGLScenePrimario::changed(int i, double val){
    modelo->moverNodosSegunShapeUnit(i, factor_inicial*zoom*val*2);
    redo_model_list();
}

void SimpleGLScenePrimario::changed2(int i, double val){
    modelo->moverMallaModeloSegunAUV(i, factor_inicial*zoom*val);
    redo_model_list();
}

void SimpleGLScenePrimario::set_zoom(float z){
    zoom = z;
    redo_model_list();
}

void SimpleGLScenePrimario::set_translation(float x, float y, float z){
    transx = x;
    transy = y;
    transz = z;
    redo_model_list();
}

void SimpleGLScenePrimario::set_rotation(float x, float y, float z){
    angle_x = x;
    angle_y = y;
    angle_z = z;
    redo_model_list();
}

void SimpleGLScenePrimario::redo_model_list(){

    Cara *c;
    Nodo* n;
    vector<int> ind_nodos;

    if(glIsList(inner_list))
        glDeleteLists(inner_list, 1);

    while( glIsList(inner_list) ){
        ++inner_list;
    }

    glNewList(inner_list, GL_COMPILE_AND_EXECUTE);

    float trtrx = diametrox*0.1*transx;
    float trtry = diametroy*0.1*transy;
    float trtrz = diametroz*0.1*transz;
    double ff =PI/30;
    double cx = cos(angle_x*ff), cy = cos(angle_y*ff), cz = cos(angle_z*ff);
    double sx = sin(angle_x*ff), sy = sin(angle_y*ff), sz = sin(angle_z*ff);

    double x1 = cz*cy, y1 = -cx*sz+cz*sx*sy, z1 = -sx*sz+cx*sy*cz;
    double x2 = cy*sz, y2 = cx*cz+sx*sy*sz, z2 = -sx*cz+cx*sy*sz;
    double x3 = -sy,   y3 = sx*cy,          z3 = cx*cy;

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (int i=0; i<= modelo->getMaxIndiceCaras(); i++){
		c=modelo->getCara(i);
		if (c!=NULL){
			ind_nodos=c->getNodos();
			glBegin(GL_TRIANGLES);
            for (int j=0; j<(int)ind_nodos.size(); j++){
                n=modelo->getNodo(ind_nodos[j]);
                double x=n->getPunto().getX();
                double y=n->getPunto().getY();
                double z=n->getPunto().getZ();

                glColor3f(0.0f,0.0f,0.0f);

                glNormal3f(n->getNormal().getPunto().getX(),n->getNormal().getPunto().getY(),n->getNormal().getPunto().getZ());
                x = x*zoom;
                y = y*zoom;
                z = z*zoom;
               double newX = (x1)*x + (y1)*y + (z1)*z;
               double newY = (x2)*x + (y2)*y + (z2)*z;
               double newZ = (x3)*x + (y3)*y + (z3)*z;

                glVertex3f(newX+ trtrx, newY + trtrz, newZ + trtry);

            }
  			glEnd();
		}
    }
	glEndList();
}

Malla *SimpleGLScenePrimario::get_malla_modelo(){
    Nodo *n;
    float trtrx = diametrox*0.1*transx;
    float trtry = diametroy*0.1*transy;
    float trtrz = diametroz*0.1*transz;
    double ff =PI/30;
    double cx = cos(angle_x*ff), cy = cos(angle_y*ff), cz = cos(angle_z*ff);
    double sx = sin(angle_x*ff), sy = sin(angle_y*ff), sz = sin(angle_z*ff);

    double x1 = cz*cy, y1 = -cx*sz+cz*sx*sy, z1 = -sx*sz+cx*sy*cz;
    double x2 = cy*sz, y2 = cx*cz+sx*sy*sz, z2 = -sx*cz+cx*sy*sz;
    double x3 = -sy,   y3 = sx*cy,          z3 = cx*cy;

    for(int i = 0; i<= modelo->getMaxIndiceNodos(); ++i){
        n = modelo->getNodo(i);
       double x = n->getPunto().getX();
       double y = n->getPunto().getY();
       double z = n->getPunto().getZ();

       x = x*zoom;
       y = y*zoom;
       z = z*zoom;

       double newX = (x1)*x + (y1)*y + (z1)*z;
       double newY = (x2)*x + (y2)*y + (z2)*z;
       double newZ = (x3)*x + (y3)*y + (z3)*z;
       n->setPunto(Punto(newX  + trtrx, newY + trtrz, newZ + trtry));
    }
    return modelo;
}

void SimpleGLScenePrimario::drawScene(){
    glCallList(list_number);

    if(glIsList(inner_list)){
        if(times < 3){
            glDeleteLists(inner_list, 1);
            ++times;
        }else{
            glCallList(inner_list);
            return;
        }
    }

    glNewList(inner_list, GL_COMPILE_AND_EXECUTE);

    Cara *c;
    Nodo* n;
    vector<int> ind_nodos;

    float trtrx = diametrox*0.1*transx;
    float trtry = diametroy*0.1*transy;
    float trtrz = diametroz*0.1*transz;
    double ff =PI/30;
    double cx = cos(angle_x*ff), cy = cos(angle_y*ff), cz = cos(angle_z*ff);
    double sx = sin(angle_x*ff), sy = sin(angle_y*ff), sz = sin(angle_z*ff);

    double x1 = cz*cy, y1 = -cx*sz+cz*sx*sy, z1 = -sx*sz+cx*sy*cz;
    double x2 = cy*sz, y2 = cx*cz+sx*sy*sz, z2 = -sx*cz+cx*sy*sz;
    double x3 = -sy,   y3 = sx*cy,          z3 = cx*cy;

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (int i=0; i<= modelo->getMaxIndiceCaras(); i++){
		c=modelo->getCara(i);
		if (c!=NULL){
			ind_nodos=c->getNodos();
			glBegin(GL_TRIANGLES);
            for (int j=0; j<(int)ind_nodos.size(); j++){
                n=modelo->getNodo(ind_nodos[j]);
                double x=n->getPunto().getX();
                double y=n->getPunto().getY();
                double z=n->getPunto().getZ();

                glColor3f(0.0f,0.0f,0.0f);

                glNormal3f(n->getNormal().getPunto().getX(),n->getNormal().getPunto().getY(),n->getNormal().getPunto().getZ());
                x = x*zoom;
                y = y*zoom;
                z = z*zoom;
               double newX = (x1)*x + (y1)*y + (z1)*z;
               double newY = (x2)*x + (y2)*y + (z2)*z;
               double newZ = (x3)*x + (y3)*y + (z3)*z;

                glVertex3f(newX+ trtrx, newY + trtrz, newZ + trtry);

            }
  			glEnd();
		}
    }
    glEndList();
}
