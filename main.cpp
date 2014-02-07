#include <iostream>
#include "csc418/robotwindow.h"

using namespace std;

int main(int argc, char* argv[])
{
    RobotWindow *win;

    Window::initWindows(argc, argv);
    win = new RobotWindow();
    win->start();

    return 0;
}

