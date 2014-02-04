#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "scene.h"

#define WINDOW_MAX_WINDOWS 8


class Window
{
private:
    std::string name; // name of the window
    int px, py; // position
    int sx, sy; // size
    int id; // id

    // scene manger
    Scene *currentScene;
public:
    // static functions
    static void initWindows(int argc, char** argv);

    Window(int posx, int posy, int sizex, int sizey, char* name);

    // Class Functions
    void resize(int w, int h);
    void update(void);

    void setScene(Scene*);

};

Window *windowList[WINDOW_MAX_WINDOWS];

#endif // WINDOW_H
