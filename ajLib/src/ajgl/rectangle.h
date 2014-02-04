#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "color.h"

class Rectangle
{
public:
    int px, py;
    int sx, sy;
    Color col;

    Rectangle();

    void Render();

    virtual void update();
};

#endif // RECTANGLE_H
