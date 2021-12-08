#include "Container.h"

#include <utility>
Container::Container(char sym)
{
  symbole = sym;
  image = "../flower_equals_win/meshes/textures/grass.png";
}

char Container::getSymbole() const
{
  return symbole;
}
void Container::setMovable(bool m)
{
  movable = m;
}
void Container::setFree(bool f)
{
  free = f;
}
bool Container::isMovable() const
{
  return movable;
}
bool Container::isFree() const
{
  return free;
}

void Container::setImage(std::string imagePath)
{
  image = std::move(imagePath);
}

std::string Container::getImage() const
{
  return image;
}
