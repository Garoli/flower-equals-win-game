#ifndef CELL_H
#define CELL_H
#include "Container.h"
class Cell {
public:
  Cell(int, int, Container *);
  int getRow() const;
  int getCol() const;
  Container * getContainer() const;
  void setContainer(Container *);
  void swapContainer(Cell *);
  bool operator==(Cell const &);

private:
  int col;
  int row;
  Container * container;
};
#endif // CELL_H
