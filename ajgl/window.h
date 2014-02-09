#ifndef WINDOW_H
#define WINDOW_H

#include <stdlib.h>
#include <unistd.h>
#include <string>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glui.h>

#include "../ajutil/ajutil.h"
#include "object.h"

// TODO figure out cross window communication
// TODO introduce "enable" feature? Window only renders and does not call updates

#define WINDOW_MAX_WINDOWS 8


class Window
{
private:
    int px, py; // position
    int sx, sy; // size
    int id; // id
    std::string name; // name of the window

protected:
    BTree objlist;

    // called before rendering and updating objects
    // called once per frame
    virtual void update();

public:
    // static functions
    static void initWindows(int argc, char** argv);
    // updates all windows when glut is idle
    static void setIdleUpdate(int);

    Window(int posx, int posy, int sizex, int sizey, const char* name);
    ~Window();

    // Class Functions
    void resize(int w, int h);
    void display();
    void start();

    int attachObject(Object*);
    int getId();
};

extern int idleUpdate; // initially set to false
extern Window *windowList[WINDOW_MAX_WINDOWS];


#endif // WINDOW_H
