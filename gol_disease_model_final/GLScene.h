
#include "life.h"

#include <ctime>

#include <GL\glut.h>


#ifndef GLSCENE_H
#define GLSCENE_H


enum Scene
{
	scene1,
	scene2
};

void GLScene(int argc, char*argv[]);
void GLScene(int, int, int argc, char*argv[]);
void Cleanup();

void newLife();

void DisplayGL();
void KeyboardGL(unsigned char c, int x, int y);
void ReshapeGL(int w, int h);

void render_mode(unsigned int mode, float off, float x_t, float y_t);
void render();
void displaytext();
#endif
