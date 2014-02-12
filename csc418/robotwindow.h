#ifndef ROBOTWINDOW_H
#define ROBOTWINDOW_H

#include "ajgl/ajgl.h"
#include "ajmath/ajmath.h"

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

    // body parts for the Robot
    Rect body;
    Rect hips;
    RobotLimb neck;
    RobotHead head;
    RobotLimb larm, rarm;
    RobotLimb lhand, rhand;
    RobotLimb lleg, rleg;

    // counter to determine what time step the transformation is in
    float animateCounter;
protected:
    void update();
public:
    RobotWindow();
};

#endif // ROBOTWINDOW_H
