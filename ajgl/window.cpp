#include "window.h"

/*
 *
 *  Window Manager
 *
 */

Window *windowList[WINDOW_MAX_WINDOWS];

void windowManagerResize(int w, int h) {
    windowList[glutGetWindow()]->resize(w,h);
}


void windowManagerUpdate(void) {
    windowList[glutGetWindow()]->display();
}

/*
 *
 * Window Class
 *
 */

void Window::initWindows(int argc, char** argv) {
    glutInit(&argc, argv);
}

Window::Window(int posx, int posy, int sizex, int sizey, const char* nm) {
    name  = nm;
    px = posx; py = posy;
    sx = sizex; sy = sizey;

    // Set video mode: double-buffered, color, depth-buffered
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Create window
    glutInitWindowPosition (posx, posy);
    glutInitWindowSize(sizex, sizey);
    id = glutCreateWindow(nm);

    if (id > WINDOW_MAX_WINDOWS) throw "Window::Window: Created too many Windows";
    else if (id == 0) throw "Window::Window: recieved 0 id";
    else if (id < 0) throw "Window::Window: negative id... ummm?";
    // else if (id < WINDOW_MAX_WINDOWS < 1) throw "Window::Window: Issue creating the window";

    windowList[id] = this;

    // Setup callback functions to handle events
    glutReshapeFunc(windowManagerResize); // Call myReshape whenever window is resized
    glutDisplayFunc(windowManagerUpdate);   // Call display whenever new frame is needed

    objlist = new BTree(destroyObject);
}

Window::~Window() {
    delete objlist;
}


void Window::start()
{
    glutMainLoop();
}

void Window::resize(int w, int h){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w/2, w/2, -h/2, h/2);

    // Update OpenGL viewport and internal variables
    glViewport(0,0, w,h);
    sx = w;
    sy = h;
}

void Window::display() {
    // render
    glClearColor(0.7f,0.7f,0.9f,1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    objlist->execAll(renderAndUpdateObject, NULL);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}
