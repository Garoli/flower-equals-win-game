//
// Created by sbrood on 09/03/2021.
//

#include "CellView.h"
#include "stb_image.h"
#include "utils.hpp"

CellView::CellView(std::string imagePath, float scale, glm::vec2 m_offset, int nbRow, int nbCol, char type)
    : vbo(GL_ARRAY_BUFFER), m_sampler(0), m_texture(GL_TEXTURE_2D), m_offset(m_offset), scale(scale), drawable(true)
{
  row = nbRow;
  col = nbCol;
  cellType = type;
  if (vao == nullptr) {
    vao = std::make_shared<VAO>(2);
    std::vector<glm::vec2> positions = {{-1. / 16, -1. / 9}, {1. / 16, -1. / 9}, {1. / 16, 1. / 9}, {-1. / 16, 1. / 9}};
    std::vector<glm::vec2> uv = {{0, 1}, {1, 1}, {1, 0}, {0, 0}};
    std::vector<uint> ibo = {0, 1, 2, 0, 2, 3};
    vao->setVBO(0, positions);
    vao->setVBO(1, uv);
    vao->setIBO(ibo);
  }

  loadImage(imagePath);
  m_sampler.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  m_sampler.setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  m_sampler.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
  m_sampler.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void CellView::loadImage(const std::string & imagePath)
{
  Image<> image;
  image.depth = 1;
  image.data = stbi_load(imagePath.c_str(), &image.width, &image.height, &image.channels, STBI_default);
  if (!image.data) {
    std::cerr << "Unable to load texture: " << imagePath << std::endl;
    exit(1);
  }
  m_texture.setData(image);
}

void CellView::draw(Program & program)
{
  m_sampler.attachToProgram(program, "color", Sampler::DoNotBind);
  m_sampler.bind();
  m_sampler.attachTexture(m_texture);
  program.setUniform("scale", scale);
  program.setUniform("offset", m_offset);
  vao->draw();
  m_sampler.unbind();
}

glm::vec2 CellView::getOffset() const
{
  return m_offset;
}

void CellView::setOffset(glm::vec2 offset)
{
  m_offset = offset;
}

void CellView::setRow(int row)
{
  CellView::row = row;
}

void CellView::setCol(int col)
{
  CellView::col = col;
}

int CellView::getRow() const
{
  return row;
}

int CellView::getCol() const
{
  return col;
}

bool CellView::isDrawable() const
{
  return drawable;
}
void CellView::setDrawable(bool drawable)
{
  CellView::drawable = drawable;
}
