
#ifndef GLITTER_SQUAREVIEW_H
#define GLITTER_SQUAREVIEW_H
#include "glApi.hpp"

class CellView {
  std::shared_ptr<VAO> vao;

public:
  void draw(Program & program);
  void setOffset(glm::vec2 offset);
  char cellType;
  glm::vec2 getOffset() const;

public:
  CellView(std::string, float scale, glm::vec2 m_offset, int, int, char);
  void setRow(int row);
  void setCol(int col);
  int getRow() const;
  int getCol() const;
  bool isDrawable() const;
  void setDrawable(bool drawable);

private:
  void loadImage(const std::string &);

private:
  Buffer vbo;
  Sampler m_sampler;
  Texture m_texture;
  int row;
  int col;
  std::vector<glm::vec2> positions;
  std::vector<glm::vec2> uv;
  glm::vec2 m_offset;
  float scale;
  bool drawable;
};

#endif
