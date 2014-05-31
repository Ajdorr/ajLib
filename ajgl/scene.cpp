#include "scene.h"

Scene::Scene(float r, float b, float g, float a, Camera* c) :
  objlist(destroyObject)
{
  bkgdRed = r;
  bkgdBlue = b;
  bkgdGreen = g;
  bkgdAlpha = a;

  mainCam = c;
}

void Scene::display()
{
  this->update();

  glClearColor(bkgdRed, bkgdGreen, bkgdBlue, bkgdAlpha);
  // glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glPushMatrix();

  if (mainCam != NULL) mainCam->lookat();

  objlist.execAll(renderAndUpdateObject, this);

  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}

int Scene::attachObject(Object* obj)
{
  return objlist.insert(obj->getName(),
                        obj->getNameLen(),
                        obj);
}
