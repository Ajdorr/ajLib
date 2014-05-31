#ifndef SCENE_H
#define SCENE_H

#include "ajutil/ajutil.h"
#include "ajgl/input.h"
#include "ajgl/object.h"
#include "ajgl/camera.h"

#include <SDL2/SDL.h>

class Scene
{
private:
  BTree objlist;

protected:
  Camera *mainCam;
  virtual void update() {}

public:
  Scene(float r, float b, float g, float a, Camera*);

  float bkgdRed, bkgdBlue, bkgdGreen, bkgdAlpha;

  void display();
  void resize(int w, int h) { if (mainCam != NULL) mainCam->resize(w,h); }
  int attachObject(Object* obj);
  void setCamera(Camera *c){ mainCam = c;}

  int getWidth() { return (mainCam != NULL) ? mainCam->getWidth() : 0; }
  int getHeight(){ return (mainCam != NULL) ? mainCam->getHeight() : 0; }
};

#endif // SCENE_H
