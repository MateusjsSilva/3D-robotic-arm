/*
 * Computacao Grafica
 * Codigo Exemplo: Biblioteca com funcao para desenhar um circulo em OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once

#ifdef __APPLE__ // MacOS
	#define GL_SILENCE_DEPRECATION
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else // Windows e Linux
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

// Include other libraries
#include <cmath> 

// Define PI if not already defined
#ifndef M_PI
	#define M_PI 3.14159265f 
#endif

// Define ESC key code if not already defined
#ifndef ESC
	#define ESC 27 
#endif