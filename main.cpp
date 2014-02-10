#include <iostream>
#include "csc418/robotwindow.h"

using namespace std;

int main(int argc, char* argv[])
{
    Window::initWindows(argc, argv);
    RobotWindow win;
    win.start();

    return 0;
}

