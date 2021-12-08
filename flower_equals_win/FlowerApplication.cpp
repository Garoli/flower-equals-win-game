#include "FlowerApplication.hpp"
#include <GLFW/glfw3.h>
#include "CellView.h"
#include "stb_image.h"
#include "utils.hpp"

FlowerApplication::FlowerApplication(int windowWidth, int windowHeight)

    : Application(windowWidth, windowHeight, "Flower equals Win"), m_vbo(GL_ARRAY_BUFFER), m_vao(2), m_program("shaders/simple2d.v.glsl", "shaders/simple2d.f.glsl"),
      m_program_bee("shaders/beeshader.v.glsl", "shaders/beeshader.f.glsl"), backgroundView("../flower_equals_win/meshes/textures/grass.png", 17, {0, 0}, 0, 0, 'G'),
      winView("../flower_equals_win/meshes/textures/win.png",8, {0, 0}, 0, 0, 'W'), key_pressed(false), button_pressed(0), game(std::string("../flower_equals_win/levels/level_1.txt")),
      m_offset({0, 0})
{
  Cell *** data = game.getGrid()->getDatas();
  for (int i = 0; i < game.getGrid()->getRowSize(); i++) {
    for (int j = 0; j < game.getGrid()->getColumnSize(); j++) {
      if (game.getGrid()->getCell(i, j)->getContainer()->getSymbole() != 'G') {
        if (game.getGrid()->getCell(i, j)->getContainer()->getSymbole() == 'B') {
          beeView = new CellView(data[i][j]->getContainer()->getImage(), 1, {0, 0}, i, j, game.getGrid()->getCell(i, j)->getContainer()->getSymbole());
          beeOrigin = {(((j + 1) * 2.0 / 16.0) - 1), (((i + 1) * 2.0 / 9.0) - 1) * -1};
        } else {
          CellView * cellView;
          cellView = new CellView(data[i][j]->getContainer()->getImage(), 1, {(((j + 1) * 2.0 / 16.0) - 1), (((i + 1) * 2.0 / 9.0) - 1) * -1}, i, j,
                                  game.getGrid()->getCell(i, j)->getContainer()->getSymbole());
          dataView.push_back(cellView);
        }
      }
    }
  }
}

void FlowerApplication::renderFrame()
{
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  m_program.bind();
  backgroundView.draw(m_program);
  std::vector<CellView *>::iterator it;
  for (it = dataView.begin(); it != dataView.end(); ++it) {
    CellView * cellView = *it;
    if (cellView->isDrawable()) {
      cellView->draw(m_program);
    }
  }
  m_program.unbind();
  m_program_bee.bind();

  beeView->setOffset(m_offset + beeOrigin);
  beeView->draw(m_program_bee);
  m_program_bee.unbind();

  if (game.getIsOver()) {
    m_program.bind();
    winView.draw(m_program);
    m_program.unbind();
  }
}


void FlowerApplication::update()
{
  GLFWwindow * window = glfwGetCurrentContext();
  if (!key_pressed && !game.getIsOver()) {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
      game.gameEnded(Direction::NORTH);
      if (game.getGrid()->canMove(game.getGrid()->getCell(beeView->getRow(), beeView->getCol()), Direction::NORTH)) {
        moveUpdate(Direction::NORTH);
      }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
      game.gameEnded(Direction::SOUTH);
      if (game.getGrid()->canMove(game.getGrid()->getCell(beeView->getRow(), beeView->getCol()), Direction::SOUTH)) {
        moveUpdate(Direction::SOUTH);
      }
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
      game.gameEnded(Direction::EAST);
      if (game.getGrid()->canMove(game.getGrid()->getCell(beeView->getRow(), beeView->getCol()), Direction::EAST)) {
        moveUpdate(Direction::EAST);
      }
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
      game.gameEnded(Direction::WEST);
      if (game.getGrid()->canMove(game.getGrid()->getCell(beeView->getRow(), beeView->getCol()), Direction::WEST)) {
        moveUpdate(Direction::WEST);
      }
    }
  } else {
    if (button_pressed == 1 && glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) {
      key_pressed = false;
    }
    if (button_pressed == 2 && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) {
      key_pressed = false;
    }
    if (button_pressed == 3 && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE) {
      key_pressed = false;
    }
    if (button_pressed == 4 && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE) {
      key_pressed = false;
    }
  }
  if (game.testAllRule()) {
    findChanges();
  }
}

void FlowerApplication::moveUpdate(Direction const direction){

    if (direction == Direction::NORTH) {
        button_pressed = 1;
    } else if (direction == Direction::SOUTH) {
        button_pressed = 2;
    } else if (direction == Direction::EAST) {
        button_pressed = 3;
    } else if (direction == Direction::WEST) {
        button_pressed = 4;
    }
    
    if (direction == Direction::NORTH || direction == Direction::SOUTH) {
        if (game.getGrid()->getCell(beeView->getRow() + direction.getRow(), beeView->getCol())->getContainer()->isFree()) {
            beeView->setRow(beeView->getRow() + direction.getRow() );
            game.getGrid()->moveBee(direction);
            } else {
            CellView * blocToMove = getNeighbourView(beeView->getRow() + direction.getRow(), beeView->getCol());
            blocToMove->setOffset({blocToMove->getOffset()[0], blocToMove->getOffset()[1] + 2. / 9 * - direction.getRow()});
            blocToMove->setRow(blocToMove->getRow() + direction.getRow());
            beeView->setRow(beeView->getRow() + direction.getRow());
            game.getGrid()->moveBee(direction);
            }
            m_offset[1] += 2. / 9 * - direction.getRow();

    } else {
        if (game.getGrid()->getCell(beeView->getRow(), beeView->getCol() + direction.getColumn())->getContainer()->isFree()) {
          beeView->setCol(beeView->getCol() + direction.getColumn() );
          game.getGrid()->moveBee(direction);
        } else {
          CellView * blocToMove = getNeighbourView(beeView->getRow(), beeView->getCol() + direction.getColumn());
          blocToMove->setOffset({blocToMove->getOffset()[0] - 2. / 16 * - direction.getColumn(), blocToMove->getOffset()[1]});
          blocToMove->setCol(blocToMove->getCol() + direction.getColumn());
          beeView->setCol(beeView->getCol() + direction.getColumn());
          game.getGrid()->moveBee(direction);
        }
        m_offset[0] += -2. / 16 * - direction.getColumn();
    }
    key_pressed = true;
}

void FlowerApplication::resize(GLFWwindow *, int framebufferWidth, int framebufferHeight)
{
  glViewport(0, 0, framebufferWidth, framebufferHeight);
}

void FlowerApplication::setCallbacks()
{
  GLFWwindow * window = glfwGetCurrentContext();
  glfwSetFramebufferSizeCallback(window, FlowerApplication::resize);
}

CellView * FlowerApplication::getNeighbourView(int row, int col)
{
  std::vector<CellView *>::iterator it;
  for (it = dataView.begin(); it != dataView.end(); ++it) {
    CellView * cellView = *it;
    if (cellView->getRow() == row && cellView->getCol() == col) {
      return cellView;
    }
  }
  return nullptr;
}
void FlowerApplication::findChanges()
{
  for (int i = 0; i < game.getGrid()->getRowSize(); i++) {
    for (int j = 0; j < game.getGrid()->getColumnSize(); j++) {
      Cell * cellGrid = game.getGrid()->getCell(i, j);
      CellView * cellView = getCellView(cellGrid);
      if (cellView && cellView->cellType != cellGrid->getContainer()->getSymbole()) {
        if (cellGrid->getContainer()->getSymbole() == 'G') {
          cellView->setDrawable(false);
        }
      }
    }
  }
}
CellView * FlowerApplication::getCellView(Cell * cellGrid)
{
  std::vector<CellView *>::iterator it;
  for (it = dataView.begin(); it != dataView.end(); ++it) {
    CellView * cellView = *it;
    if (cellGrid->getCol() == cellView->getCol() && cellGrid->getRow() == cellView->getRow()) {
      return cellView;
    }
  }
  return nullptr;
}

// TODO
void FlowerApplication::usage(std::string & shortDescritpion, std::string & synopsis, std::string & description)
{
  shortDescritpion = "Application for programming assignment 1";
  synopsis = "pa1 <part>";
  description = "  A minimal application displaying a yellow rectangle on white background.\n"
                "  Two parts are available in this tutorial, and a command argument (<part>)\n"
                "  can be used to specify which one to launch.\n";
}
