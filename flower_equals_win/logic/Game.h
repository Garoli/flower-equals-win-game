#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "Grid.h"
#include "Rule.h"
#include "Direction.h"
class Game {
public:
  explicit Game(const std::string &);
  Grid * getGrid() const;
  bool testAllRule();
  void gameEnded(Direction);

private:
  Grid * grid;
  std::vector<Rule *> rules;
  bool isOver;

public:
  bool getIsOver() const;
};
#endif
