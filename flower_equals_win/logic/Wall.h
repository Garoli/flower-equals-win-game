#ifndef WALL_H
#define WALL_H
#include "Obstacle.h"

class Wall : public Obstacle {
public:
  explicit Wall(char);
};
#endif // WALL_H
