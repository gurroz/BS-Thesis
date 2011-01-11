// Código adaptado desde la lección 6 de Nehe.. créditos a continuación:
//
// This code was created by Jeff Molofee '99 (ported to Linux/GLUT by Richard Campbell '99)
//
// If you've found this code useful, please let me know.
//
// Visit me at www.demonews.com/hosted/nehe
// (email Richard Campbell at ulmont@bellsouth.net)
//

// el cambio es que ahora simplemente incluyen este archivo y cargan la textura.

#ifndef _LOAD_TEXTURES_H
#define _LOAD_TEXTURES_H

#include <GL/gl.h>	// Header File For The OpenGL32 Library

// Load Bitmaps And Convert To Textures
GLuint LoadGLTexture(const char *file);

#endif
