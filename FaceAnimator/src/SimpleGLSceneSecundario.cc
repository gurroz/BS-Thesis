// generated 2006/7/27 1:06:45 CLT by chupacabrasx@amd64-3000.(none)
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to SimpleGLScene.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "SimpleGLSceneSecundario.hh"

SimpleGLSceneSecundario::SimpleGLSceneSecundario(SimpleGLScene* m, float rot) : SimpleGLScene()
{
	this->father = m;
	//this->father->realize();
    this->copy_scene_values(m);
	this->rotation = rot;

  //
  // Set OpenGL-capability to the widget.
  //
  set_gl_capability(father->get_gl_config(), father->get_gl_context(), true);
}

SimpleGLSceneSecundario::~SimpleGLSceneSecundario()
{
}

void SimpleGLSceneSecundario::drawScene(){
    glRotatef(rotation, 0.0f, 1.0f, 0.0f);
    father->drawScene();
}
