#include "camera.h"

Camera::Camera(const char* n, Vector3& pos, Vector3& t, Vector3& u,
               int w, int h) :
  Object(n, pos),
  width(w),
  height(h),
  tar(t),
  up(u)
{
  nearplane = 1.0d;
  farplane = 5000.0d;
}

void Camera::resize(int w, int h)
{
  width = w; height = h;
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // TODO add to camera class
  gluPerspective(fov, (GLdouble)w/(GLdouble)h, nearplane, farplane);

}

void Camera::render()
{
  gluLookAt((GLdouble)pos.x(), (GLdouble)pos.y(), (GLdouble)pos.z(),
            (GLdouble)tar.x(), (GLdouble)tar.y(), (GLdouble)tar.z(),
            (GLdouble)up.x(), (GLdouble)up.y(), (GLdouble)up.z());
}
