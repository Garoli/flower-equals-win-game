#include "DeleteWallRule.h"
DeleteWallRule::DeleteWallRule(Container * o, Container * l, Container * r) : Rule(o, l, r) {}
void DeleteWallRule::execute(Grid * grid)
{
  grid->removeAllWall();
}