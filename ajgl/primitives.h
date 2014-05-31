#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glui.h> // Get rid of this later...

#include "ajmath/ajmath.h"
#include "ajgl/object.h"

class Circ : public Object
{
protected:
    void render();
    void update();

public:
    float radius; // radius

    Circ(const char*, float radius,
         const Vector3 &p = Vector3::Zero,
         const Vector3 &rotation = Vector3::Zero,
         const Vector3 &scale = Vector3::One);

};

// class Rect : public Object
class Rect : public Object
{
protected:
    void render();
    void update();

public:
    float sx, sy;

    Rect(const char*, float sizex, float sizey,
         const Vector3 &pos = Vector3::Zero,
         const Vector3 &r = Vector3::Zero,
         const Vector3 &s = Vector3::One);

};

class Cube : public Object
{
protected:
    void render();
    void update();
public:
    float sx, sy, sz;

    Cube(const char*, float x, float y, float z,
         const Vector3 &pos = Vector3::Zero,
         const Vector3 &rotation = Vector3::Zero,
         const Vector3 &size = Vector3::One);
};

/*
  WIP need to make a cylinder
*/
// Cylinder by default is aligned to the z-axis
class Cylinder : public Object
{
private:
    float *pointsx, *pointsy;
    unsigned int total;
    float radius, height;

    void createPoints();
protected:
    void render();
    void update();
public:

    Cylinder(const char*, float rad, float hg,
         const Vector3 &p = Vector3::Zero,
         const Vector3 &rotation = Vector3::Zero,
         const Vector3 &size = Vector3::One);
};


#endif // PRIMITIVES_H
