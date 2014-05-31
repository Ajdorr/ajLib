#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "ajmath/ajmath.h"
#include "ajgl/object.h"

class Camera : public Object
{
private:
  int width, height;
  float fov;
  double nearplane, farplane;
  Vector3 tar, up;

protected:
  virtual void update() {}
  virtual void render();

public:
  Camera(const char*, Vector3& pos, Vector3& tar, Vector3& u,
         int width = 640, int height = 480);

  void resize(int w, int h);
  int getWidth(){ return width; }
  int getHeight(){ return height; }
  void lookat() { this->render();}
};

#endif // CAMERA_H
