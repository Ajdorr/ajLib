#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <GL/glut.h>
#include "ajutil/ajutil.h"
#include "ajmath/ajmath.h"

/*
 *
 * Notes: Scale manipulations are applied only to the object itself
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
    Vector3 pos, scale, rot;

    // objects at least need a name
    Object(const char*, Vector3 p = ajMath::Zero,
           Vector3 s = ajMath::One, Vector3 r = ajMath::Zero);

    virtual ~Object();

    // Graphic Function
    void renderUpdate();
    // Rotate around a point, the point is relative to the parent
    void rotateAround(Vector3 relativePoint, Vector3 axis, float angle);

    int attachChild(Object*);

    // Accessor Functions
    const char* getName();
    unsigned int getNameLen();

};

#endif // OBJECT_H
