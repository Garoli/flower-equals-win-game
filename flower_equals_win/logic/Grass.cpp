#include "Grass.h"
Grass::Grass(char s) : Container(s)
{
  setFree(true);
  setImage("../flower_equals_win/meshes/textures/grass.png");
}
