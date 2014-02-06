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

#define WINDOW_MAX_WINDOWS 8

class Window
{
private:
    int px, py; // position
    int sx, sy; // size
    int id; // id
    std::string name; // name of the window

    BTree* objlist;
public:
    // static functions
    static void initWindows(int argc, char** argv);

    Window(int posx, int posy, int sizex, int sizey, char* name);
    ~Window();

    // Class Functions
    void resize(int w, int h);
    void display();
};


#endif // WINDOW_H
