#include "Direction.h"
#include <vector>
const Direction Direction::NORTH = Direction(-1, 0);
const Direction Direction::EAST = Direction(0, 1);
const Direction Direction::SOUTH = Direction(1, 0);
const Direction Direction::WEST = Direction(0, -1);
int Direction::getRow() const
{
  return row;
}
int Direction::getColumn() const
{
  return column;
}
std::vector<Direction> listDirection()
{
  std::vector<Direction> vect;
  vect.push_back(Direction::NORTH);
  vect.push_back(Direction::EAST);
  vect.push_back(Direction::SOUTH);
  vect.push_back(Direction::WEST);
  return vect;
}

bool operator ==(Direction direction1, Direction direction2){
  if ((direction1.getRow() == direction2.getRow()) && (direction1.getColumn() == direction2.getColumn())){
    return true;
  } else {
    return false;
  }
}