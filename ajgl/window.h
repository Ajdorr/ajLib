#ifndef WINDOW_H
#define WINDOW_H

#include <stdlib.h>
#include <unistd.h>
#include <string>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glui.h>

#include "ajutil/ajutil.h"
#include "ajgl/object.h"
#include "ajgl/scene.h"

// TODO introduce "enable" feature? Window only renders and does not call updates

namespace Input
{
  int getKey(unsigned char);
  int getKeyUp(unsigned char);
  int getKeyDown(unsigned char);
}

int windowInit(int argc, char** argv, const char* nm);
void windowSetScene(Scene *s);
Scene* windowGetScene();
void windowMainLoop();
// int attachObject(Object* obj);
int windowGetId();

// WIP
void windowLimitFramerate(int);
int windowloadScene(const char*);

#endif // WINDOW_H
