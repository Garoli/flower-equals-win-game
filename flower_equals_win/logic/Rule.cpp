#include "Rule.h"
#include "Cell.h"
Rule::Rule(Container * o, Container * l, Container * r)
{
  operation = o;
  leftOperand = l;
  rightOperand = r;
}
Container * Rule::getLeftOperand() const
{
  return leftOperand;
}
Container * Rule::getRightOperand() const
{
  return rightOperand;
}
Container * Rule::getOperator() const
{
  return operation;
}
bool Rule::isExecutable(Grid * grid) const
{
  bool leftPresent = false, rightPresent = false;
  std::vector<Cell *> neighbors = grid->getNeighbors(grid->getCell(getOperator()));
  for (Cell * cell : neighbors) {
    if (*cell == *(grid->getCell(getLeftOperand()))) {
      leftPresent = true;
    }
    if (*cell == *(grid->getCell(getRightOperand()))) {
      rightPresent = true;
    }
  }
  return rightPresent && leftPresent;
}