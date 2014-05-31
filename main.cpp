#include <iostream>
#include "ajlib.h"

using namespace std;

int main(int argc, char* argv[])
{
  Vector3 e(1,0,0), t(0,0,0), u(0,0,1);
  Camera cam("Player Camera", e,t,u);
  Scene newScene(0.3, 0.5, 0.3, 1.0, &cam);
  Cube player("player", 1,1,1, Vector3(0,0,0));
  // player.attachMaterial(&Material::Crimson);
  // newScene.attachObject(&cam);
  newScene.attachObject(&player);

  windowSetScene(&newScene);

  windowInit(argc, argv, "My Window");

  windowMainLoop();

  return 0;
}

