#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <GL/glut.h>
#include "../ajutil/ajutil.h"
#include "../ajmath/ajmath.h"

// helper functions, don't use these!
void destroyObject(void*);
void renderAndUpdateObject(void*, void*);

class Object
{
private:
    // Transform
    // position, rotation, and scale
    Vector3 pos, rot, scale;
    BTree children;
    std::string name; // this acts as the key for the binary tree

protected:
    virtual void update();
    virtual void render();

public:
    void renderUpdate();

    Object(std::string&); // objects at least need a name
    virtual ~Object();

    int attachChild(Object*);
};

#endif // OBJECT_H
