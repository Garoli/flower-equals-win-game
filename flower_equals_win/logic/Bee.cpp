#include "Bee.h"
Bee::Bee(char sym) : Container(sym)
{
  setMovable(true);
  setImage("../flower_equals_win/meshes/textures/bee.png");
}