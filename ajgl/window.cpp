#include "window.h"

/*
 *
 *  Window Manager
 *
 */

Window *windowList[WINDOW_MAX_WINDOWS];
int idleUpdate;

void windowManagerResize(int w, int h) {
    if (windowList[glutGetWindow()] != NULL)
        windowList[glutGetWindow()]->resize(w,h);
}


void windowManagerDisplay(void) {
    if (windowList[glutGetWindow()] != NULL)
        windowList[glutGetWindow()]->display();
}

void windowManagerDisplayAll(void)
{
    int i;
    for (i=0; i < WINDOW_MAX_WINDOWS; i++) {
        if (windowList[i] != NULL) {
            glutSetWindow(i);
            glutPostRedisplay();
        }
    }

    usleep(50000);
}

/*
 *
 * Window Class
 *
 */

void Window::update(){}

void Window::initWindows(int argc, char** argv) {
    glutInit(&argc, argv);
    idleUpdate = 0;
}

void Window::setIdleUpdate(int) {
    if (idleUpdate) GLUI_Master.set_glutIdleFunc(windowManagerDisplayAll);
    else GLUI_Master.set_glutIdleFunc(NULL);
}

Window::Window(int posx, int posy, int sizex, int sizey, const char* nm):
    objlist(destroyObject)
{
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
    glutDisplayFunc(windowManagerDisplay);   // Call display whenever new frame is needed

}

Window::~Window() {
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
    // render objects
    update();

    glClearColor(0.7f,0.7f,0.9f,1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    objlist.execAll(renderAndUpdateObject, NULL);

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}


int Window::attachObject(Object* obj)
{
    return objlist.insert(obj->getName(),
                          obj->getNameLen(),
                          obj);
}

int Window::getId()
{
    return id;
}
