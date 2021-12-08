#ifndef RULE_H
#define RULE_H
#include "Cell.h"
#include "Container.h"
#include "Grid.h"
class Rule {
public:
  Rule(Container *, Container *, Container *);
  Container * getLeftOperand() const;
  Container * getRightOperand() const;
  Container * getOperator() const;
  virtual void execute(Grid *) = 0;
  bool isExecutable(Grid *) const;

private:
  Container * operation;
  Container * leftOperand;
  Container * rightOperand;
};
#endif
