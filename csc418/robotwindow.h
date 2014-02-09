#ifndef ROBOTWINDOW_H
#define ROBOTWINDOW_H

#include "ajgl/ajgl.h"
#include "ajmath/ajmath.h"

class Circ : public Object {
protected:
    Vector3 color; // colour
    void render();
    void update();

public:
    float radius; // radius

    Circ(const char*, float radius,
           Vector3 col, Vector3 p = ajMath::Zero,
           Vector3 s = ajMath::One, Vector3 rot = ajMath::Zero);

};

class Rect : public Object {
protected:
    Vector3 color;
    void render();
    void update();

public:
    float sx, sy;

    Rect(const char*, float sizex, float sizey,
           Vector3 col, Vector3 p = ajMath::Zero,
           Vector3 s = ajMath::One, Vector3 r = ajMath::Zero);

};

class RobotLimb :public Rect {
private:
    Circ joint;
protected:
    void render();
    void update();
public:
    Vector3 hinge;
    float angle;
    float posx;
    float extend;

    RobotLimb(const char*, Vector3 col, Vector3 position,
             Vector3 hingePosition, Vector3 rotation = ajMath::Zero);
};

class RobotHead : public Rect {
private:
    Circ leyeOut, leyeIn;
    Circ reyeOut, reyeIn;
protected:
    void render();
    void update(){;}
public:
    RobotHead(const char* name, Vector3 col, Vector3 pos);
};

class RobotWindow : public Window {
private:
    GLUI *controls;

    Rect body;
    Rect hips;
    RobotLimb neck;
    RobotHead head;
    RobotLimb larm, rarm;
    RobotLimb lhand, rhand;
    RobotLimb lleg, rleg;

    float animateCounter;
    // Rect rarm, rhand;
protected:
    void update();
public:
    RobotWindow();
};

#endif // ROBOTWINDOW_H
