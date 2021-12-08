#ifndef CONTAINER_H
#define CONTAINER_H
#include <string>
class Container {
public:
  explicit Container(char);
  char getSymbole() const;
  void setMovable(bool);
  void setFree(bool);
  bool isMovable() const;
  bool isFree() const;
  void setImage(std::string);
  std::string getImage() const;

private:
  char symbole;
  bool movable = false;
  bool free = false;
  std::string image;
};
#endif // CONTAINER_H
