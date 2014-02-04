#ifndef OBJECT2D_H
#define OBJECT2D_H

class Object2D
{
private:
    int children;
public:
    int px, py;

    Object2D();

    Object2D *parent;
    Object2D **children;
};

#endif // OBJECT2D_H
