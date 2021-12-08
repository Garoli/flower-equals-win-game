#ifndef GRID_H
#define GRID_H
#include <string>
#include <vector>
#include "Cell.h"
#include "Direction.h"
class Grid {
public:
  explicit Grid(const std::string &);
  void display() const;
  Cell * getCell(int, int) const;
  bool isCoordinateValid(int, int) const;
  std::vector<Cell *> getNeighbors(Cell *) const;
  static void moveTo(Cell *, Cell *);
  void move(Cell *, Direction);
  void moveBee(Direction);
  bool canMove(Cell *, Direction) const;
  void removeAllWall();
  Cell * getCell(Container *);
  Cell *** getDatas() const;
  int getColumnSize() const;
  int getRowSize() const;
  bool canPushBlock(int, int, Direction) const;
  bool isOver(Direction) const;
private:
  int columnSize;
  int rowSize;
  Cell *** datas;
  Cell * beeCell;
};
#endif // GRID_H
