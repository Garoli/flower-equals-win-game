#ifndef DELETEWALLRULE_H
#define DELETEWALLRULE_H
#include "Grid.h"
#include "Rule.h"
class DeleteWallRule : public Rule {
public:
  DeleteWallRule(Container *, Container *, Container *);
  void execute(Grid *) override;
  bool isExecutable(Grid *);
};
#endif
