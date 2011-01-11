

#ifndef _SIMPLEGLSCENESECUNDARIO_HH

#include "SimpleGLScene.hh"

#  define _SIMPLEGLSCENESECUNDARIO_HH

class SimpleGLSceneSecundario : public SimpleGLScene
{
public:
        SimpleGLSceneSecundario(SimpleGLScene *gl_scene_primario, float rotation = 90.0f);
		~SimpleGLSceneSecundario();
		void drawScene();
private:
        SimpleGLScene* father;
        float rotation;
};

#endif
