#include "primitives.h"

Circ::Circ(const char* name, float rad,
     const Vector3 &p, const Vector3 &r, const Vector3 &s):
    Object(name, p, r, s)
{
    radius = rad;
}

// WIP memoize this
void Circ::render() {
    float i;
    float inc = 2*PI/20; // TODO make this a good function of radius or something
    // float inc = 0.1;
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < DPI; i+=inc) {
        glVertex2f(radius*cos(i), radius*sin(i));
    }
    glEnd();
}

void Circ::update() {

}

Rect::Rect(const char* name, float x, float y,
           const Vector3 &p, const Vector3 &r, const Vector3 &s):
    Object(name, p, r, s)
{
    sx = x;
    sy = y;
}

void Rect::render() {
    glBegin(GL_QUADS);
    glVertex2f(-sx/2, -sy/2);
    glVertex2f(sx/2, -sy/2);
    glVertex2f(sx/2, sy/2);
    glVertex2f(-sx/2, sy/2);
    glEnd();
}

void Rect::update() {

}


Cube::Cube(const char* name, float x, float y, float z,
           const Vector3 &p, const Vector3 &r, const Vector3 &s):
    Object(name, p, r, s)
{
    sx = x;
    sy = y;
    sz = z;
}

void Cube::render() {
    glBegin(GL_QUADS);

    // front
    glVertex3f(-sx/2, -sy/2,  sz/2);
    glVertex3f( sx/2, -sy/2,  sz/2);
    glVertex3f( sx/2,  sy/2,  sz/2);
    glVertex3f(-sx/2,  sy/2,  sz/2);

    // back
    glVertex3f( sx/2, -sy/2, -sz/2);
    glVertex3f(-sx/2, -sy/2, -sz/2);
    glVertex3f(-sx/2,  sy/2, -sz/2);
    glVertex3f( sx/2,  sy/2, -sz/2);

    // left
    glVertex3f(-sx/2, -sy/2, -sz/2);
    glVertex3f(-sx/2, -sy/2,  sz/2);
    glVertex3f(-sx/2,  sy/2,  sz/2);
    glVertex3f(-sx/2,  sy/2, -sz/2);

    // right
    glVertex3f( sx/2, -sy/2,  sz/2);
    glVertex3f( sx/2, -sy/2, -sz/2);
    glVertex3f( sx/2,  sy/2, -sz/2);
    glVertex3f( sx/2,  sy/2,  sz/2);

    // top
    glVertex3f(-sx/2,  sy/2,  sz/2);
    glVertex3f( sx/2,  sy/2,  sz/2);
    glVertex3f( sx/2,  sy/2, -sz/2);
    glVertex3f(-sx/2,  sy/2, -sz/2);

    // bottom
    glVertex3f(-sx/2, -sy/2, -sz/2);
    glVertex3f( sx/2, -sy/2, -sz/2);
    glVertex3f( sx/2, -sy/2,  sz/2);
    glVertex3f(-sx/2, -sy/2,  sz/2);

    glEnd();
}

void Cube::update() {}

Cylinder::Cylinder(const char* name, float rad, float hg,
           const Vector3 &p, const Vector3 &r,
           const Vector3 &s):
    Object(name, p, r, s)
{
    radius = rad;
    height = hg;
    total = (unsigned int)(2*radius) + 20;

    pointsx = NULL;
    pointsy = NULL;

    createPoints();
}

void Cylinder::createPoints() {
    unsigned int i;
    float inc = DPI/total, count;
    if (pointsx) delete[] pointsx;
    if (pointsy) delete[] pointsy;

    pointsx = new float[total];
    pointsy = new float[total];

    for (i = 0, count = 0; count < DPI; i++, count += inc) {
        pointsx[i] = radius * cos(count);
        pointsy[i] = radius * sin(count);
    }

}

// WIP Test and Optimize
void Cylinder::render() {
    unsigned int i;

    // draw front face
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f( 0.0f, 0.0f, height/2);
    for (i = 0; i < total; i++)
        glVertex3f( pointsx[i], pointsy[i], height/2);
    glVertex3f( pointsx[0], pointsy[0], height/2);
    glEnd();

    // draw rear face
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f( 0.0f, 0.0f, -height/2);
    for (i = 0; i < total; i++)
        glVertex3f( pointsx[i], pointsy[i], -height/2);
    glVertex3f( pointsx[0], pointsy[0], -height/2);
    glEnd();

    // draw sides
    glBegin(GL_QUADS);
    for (i = 1; i < total; i++) {
        glVertex3f( pointsx[i-1], pointsy[i-1], height/2);
        glVertex3f( pointsx[i-1], pointsy[i-1], -height/2);
        glVertex3f( pointsx[i], pointsy[i], -height/2);
        glVertex3f( pointsx[i], pointsy[i], height/2);
    }
    glVertex3f( pointsx[total-1], pointsy[total-1], height/2);
    glVertex3f( pointsx[total-1], pointsy[total-1], -height/2);
    glVertex3f( pointsx[0], pointsy[0], -height/2);
    glVertex3f( pointsx[0], pointsy[0], height/2);

    glEnd();
}

void Cylinder::update() {}
