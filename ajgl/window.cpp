#include "window.h"


/*
 *
 * Input
 *
 */

BTree keyDown(NULL);
int mouseDeltaX, mouseDeltaY;
int mousePosX, mousePosY;
char mouseDown[8];
char keyboardDown[256];

void inputPressKey(unsigned char c, int, int)
{
  keyboardDown[(int)c] = 0xFF;
  keyDown.insert(&c, sizeof(char), (void*)0xFFFFFFFF);
}

void inputReleaseKey(unsigned char c, int, int) { keyboardDown[(int)c] = 0x0; }
void inputClearKeyPress() { keyDown.removeAll(); }

void inputMousePress(int b, int s, int x, int y)
{
  mouseDeltaX = x - mousePosX;
  mouseDeltaY = y - mousePosY;
  mousePosX = x;
  mousePosY = y;

  if (s == GLUT_UP) mouseDown[(int)b] = 0x0;
  else mouseDown[(int)b] = 0xFF;
}

void inputMouseMove(int x, int y)
{
  mouseDeltaX = x - mousePosX;
  mouseDeltaY = y - mousePosY;
  mousePosX = x;
  mousePosY = y;
}

/*
void mouseEnter(int state);
void mouseExit(int state);
*/

int Input::getKey(unsigned char c) { return (mouseDown[(int)c] != 0x0); }
int Input::getKeyDown(unsigned char c) { return (mouseDown[(int)c] == 0x0); }
int Input::getKeyUp(unsigned char c)
{
  return (keyDown.search(&c, sizeof(char)) != NULL);
}

/*
 *
 * Window Class
 *
 */

int id;
std::string name; // name of the window
Scene *currScene;

void windowResize(int w, int h)
{
  if (currScene != NULL) currScene->resize(w,h);
}

void windowDisplay()
{
  if (currScene != NULL)
    currScene->display();
}

int windowInit(int argc, char** argv, const char* nm)
{
    glutInit(&argc, argv);
    // Set video mode: double-buffered, color, depth-buffered
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    // Create window and set local variables
    name = nm;
    if (currScene != NULL)
      glutInitWindowSize(currScene->getWidth(), currScene->getHeight());
    id = glutCreateWindow(nm);

    if (id <= 0) return -1;

    // windowList[id] = this;
    glutDisplayFunc(windowDisplay);
    glutReshapeFunc(windowResize);
    glutKeyboardFunc(inputPressKey);
    glutKeyboardUpFunc(inputReleaseKey);
    glutMouseFunc(inputMousePress);
    glutMotionFunc(inputMouseMove);
    glutPassiveMotionFunc(inputMouseMove);

    /* WIP
    glutSpecialFunc();
    glutSpecialFuncUp();
    glutVisibilityFunc();
    glutEntryFunc();
    glutIdleFunc();
    */

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    return 0;
}

void windowSetScene(Scene *s) { currScene = s; }
Scene* windowGetScene() { return currScene; }
int windowGetId() { return id; }
void windowMainLoop() { glutMainLoop(); }
