#include "Cell.h"
Cell::Cell(const int ro, const int co, Container * data)
{
  row = ro;
  col = co;
  container = data;
}
int Cell::getRow() const
{
  return row;
}
int Cell::getCol() const
{
  return col;
}
Container * Cell::getContainer() const
{
  return container;
}
void Cell::setContainer(Container * cont)
{
  container = cont;
}
void Cell::swapContainer(Cell * other)
{
  Container * tmp = container;
  setContainer(other->getContainer());
  other->setContainer(tmp);
}
bool Cell::operator==(const Cell & other)
{
  return other.getCol() == col && other.getRow() == row;
}