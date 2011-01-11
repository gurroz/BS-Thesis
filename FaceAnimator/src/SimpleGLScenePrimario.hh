

#ifndef _SIMPLEGLSCENEPRIMARIO_HH

#include "SimpleGLScene.hh"

#  define _SIMPLEGLSCENEPRIMARIO_HH

class SimpleGLScenePrimario : public SimpleGLScene
{
public:
        SimpleGLScenePrimario(Malla* malla, Malla* modelo);
		~SimpleGLScenePrimario();
        void drawScene();
        void changed(int i, double val);
        void changed2(int i, double val);
        void set_zoom(float z);
        void set_translation(float x, float y, float z);
        void set_rotation(float x, float y, float z);
        float transx, transy, transz;
        Malla *get_malla_modelo();
        double get_factor_inicial();
protected:
        void on_realize();
private:
        float zoom;
        double factor_inicial;
        float angle_x, angle_y, angle_z;
		Malla *malla;
		Malla *modelo;
		GLuint list_number;
		GLuint inner_list;
		float diam;
		void redo_model_list();
		int times;
};

#endif
