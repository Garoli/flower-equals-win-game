#include "Game.h"
#include "BlockWall.h"
#include "DeleteWallRule.h"
Game::Game(const std::string & filename) : isOver(false)
{
  grid = new Grid(filename);
  rules.push_back(new DeleteWallRule(grid->getCell(7, 8)->getContainer(), grid->getCell(4, 14)->getContainer(), grid->getCell(1, 2)->getContainer()));
}
Grid * Game::getGrid() const
{
  return grid;
}

bool Game::testAllRule()
{
  bool ruleExecuted =false;
  for (Rule * rule : rules) {
    if (rule->isExecutable(grid)) {
      rule->execute(grid);
      ruleExecuted=true;
    }
  }
  return ruleExecuted;
}

void Game::gameEnded(Direction direction)
{
  isOver = grid->isOver(direction);
}

bool Game::getIsOver() const
{
  return isOver;
}
