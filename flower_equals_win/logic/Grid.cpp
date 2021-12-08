#include "Grid.h"
#include <fstream>
#include <iostream>
#include "Bee.h"
#include "BlockWall.h"
#include "Container.h"
#include "Direction.h"
#include "Flower.h"
#include "Grass.h"
#include "Minus.h"
#include "Wall.h"
Grid::Grid(const std::string & filename)
{
  int row = 0, col = 0;
  char c;
  std::ifstream infile(filename);
  if (infile.is_open()) {
    infile >> row >> col;
    rowSize = row;
    columnSize = col;
    datas = (Cell ***)malloc(rowSize * sizeof(Cell **));
    for (int i = 0; i < rowSize; ++i) {
      datas[i] = (Cell **)malloc(columnSize * sizeof(Cell *));
      for (int j = 0; j < columnSize; ++j) {
        infile >> c;
        switch (c) {
        case 'G':
          datas[i][j] = new Cell(i, j, new Grass('G'));
          break;
        case 'B':
          datas[i][j] = new Cell(i, j, new Bee('B'));
          beeCell = datas[i][j];
          break;
        case 'F':
          datas[i][j] = new Cell(i, j, new Flower('F'));
          break;
        case 'W':
          datas[i][j] = new Cell(i, j, new Wall('W'));
          break;
        case '-':
          datas[i][j] = new Cell(i, j, new Minus('-'));
          break;
        case 'M':
          datas[i][j] = new Cell(i, j, new BlockWall('M'));
          break;
        default:
          datas[i][j] = new Cell(i, j, new Grass('G'));
          break;
        }
      }
    }
  }
}
void Grid::display() const
{
  for (int i = 0; i < rowSize; ++i) {
    for (int j = 0; j < columnSize; ++j) {
      std::cout << datas[i][j]->getContainer()->getSymbole();
    }
    std::cout << "" << std::endl;
  }
}
Cell * Grid::getCell(int row, int col) const
{
  return datas[row][col];
}

bool Grid::isCoordinateValid(int row, int col) const
{
  return row >= 0 && row < rowSize && col >= 0 && col < columnSize;
}

std::vector<Cell *> Grid::getNeighbors(Cell * origin) const
{
  std::vector<Cell *> vect;
  std::vector<Direction> directions = listDirection();
  for (Direction value : directions) {
    if (isCoordinateValid(value.getRow() + origin->getRow(), value.getColumn() + origin->getCol())) {
      vect.push_back(getCell(value.getRow() + origin->getRow(), value.getColumn() + origin->getCol()));
    }
  }
  return vect;
}
void Grid::moveTo(Cell * origin, Cell * destination)
{
  origin->swapContainer(destination);
}
bool Grid::canMove(Cell * origin, Direction d) const
{
  if (isCoordinateValid(origin->getRow() + d.getRow(), origin->getCol() + d.getColumn())) {
    Cell * destination = getCell(origin->getRow() + d.getRow(), origin->getCol() + d.getColumn());
    if (destination->getContainer()->isFree()) {
      return true;
    } else {
      if (canPushBlock(origin->getRow(), origin->getCol(), d)) {
        return true;
      }
      return false;
    }
  }
  return false;
}

void Grid::move(Cell * origin, Direction d)
{
  Cell * destination = getCell(origin->getRow() + d.getRow(), origin->getCol() + d.getColumn());
  if (destination->getContainer()->isFree()) {
    moveTo(origin, destination);
    beeCell = destination;
  } else {
    if (canPushBlock(origin->getRow(), origin->getCol(), d)) {
      Cell * nextDestination = getCell(destination->getRow() + d.getRow(), destination->getCol() + d.getColumn());
      moveTo(destination, nextDestination);
      beeCell = destination;
      moveTo(origin, destination);
    }
  }
}

void Grid::moveBee(Direction d)
{
  move(beeCell, d);
}
void Grid::removeAllWall()
{
  for (int i = 0; i < rowSize; ++i) {
    for (int j = 0; j < columnSize; ++j) {
      if (datas[i][j]->getContainer()->getSymbole() == 'W') {
        datas[i][j]->setContainer(new Grass('G'));
      }
    }
  }
}
Cell * Grid::getCell(Container * container)
{
  for (int i = 0; i < rowSize; ++i) {
    for (int j = 0; j < columnSize; ++j) {
      if (datas[i][j]->getContainer() == container) {
        return datas[i][j];
      }
    }
  }
  return nullptr;
}
Cell *** Grid::getDatas() const
{
  return datas;
}

int Grid::getColumnSize() const
{
  return columnSize;
}

int Grid::getRowSize() const
{
  return rowSize;
}

bool Grid::canPushBlock(int row, int col, Direction d) const
{
  Cell * destination = getCell(row + d.getRow(), col + d.getColumn());
  if (destination->getContainer()->isMovable() && isCoordinateValid(destination->getRow() + d.getRow(), destination->getCol() + d.getColumn())) {
    Cell * nextDestination = getCell(destination->getRow() + d.getRow(), destination->getCol() + d.getColumn());
    return nextDestination->getContainer()->isFree();
  }
  return false;
}
bool Grid::isOver(Direction d) const{
    return isCoordinateValid(beeCell->getRow() + d.getRow(), beeCell->getCol() + d.getColumn())
           && getCell(beeCell->getRow() + d.getRow(), beeCell->getCol() + d.getColumn())->getContainer()->getSymbole() == 'F';
}