#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <GL/glut.h>
#include "ajutil/ajutil.h"
#include "ajmath/ajmath.h"
#include "ajgl/material.h"

/*
 *
 * Object Class
 * Anything rendered to the window is an object and inherit from this class
 * There are also primitives that can be used in primitives.h
 *
 */

// helper functions, don't use these!
void destroyObject(void*);
void renderAndUpdateObject(void*, void*);

class Object
{
private:
    // Transform
    // position, rotation, and scale
    std::string name; // this acts as the key for the binary tree
    BTree children;

protected:

    virtual void update();
    virtual void render();

public:
    Material *mat;
    Vector3 pos, scale, rot;

    // objects at least need a name
    Object(const char*, const Vector3 &p = Vector3::Zero,
           const Vector3 &r = Vector3::Zero, const Vector3 &s = Vector3::One);

    virtual ~Object();

    // Graphic Function
    void display();
    // Rotate around a point in object space
    void rotateAround(const Vector3 &relativePoint,
                      const Vector3 &axis, const float angle);

    int attachChild(Object*);
    void attachMaterial(Material*);

    // Accessor Functions
    const char* getName();
    unsigned int getNameLen();

};

#endif // OBJECT_H
