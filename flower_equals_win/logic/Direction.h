#ifndef DIRECTION_H
#define DIRECTION_H
#include <vector>
class Direction {
public:
  // Enum value DECLARATIONS - they are defined later
  static const Direction NORTH;
  static const Direction EAST;
  static const Direction SOUTH;
  static const Direction WEST;

private:
  int row;    // in kilograms
  int column; // in meters

private:
  Direction(double row, double column)
  {
    this->row = row;
    this->column = column;
  }

public:
  int getRow() const;
  int getColumn() const;
};
bool operator ==(Direction direction1, Direction direction2);
std::vector<Direction> listDirection();
#endif
