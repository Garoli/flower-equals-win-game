#ifndef __PA1_APPLICATION_H__
#define __PA1_APPLICATION_H__
#include <memory>
#include "Application.hpp"
#include "CellView.h"
#include "glApi.hpp"
#include "logic/Game.h"

// forward declarations
struct GLFWwindow;

/// A concrete implementation of Application for PA1
class FlowerApplication : public Application {
public:
  /**
   * @brief Constructor
   * @param windowWidth initial width of the application
   * @param windowHeight initial height of the application
   * @param part should be 1 or 2 to select the corresponding tutorial part
   */
  FlowerApplication(int windowWidth, int windowHeight);
  void setCallbacks() override;
  static void usage(std::string & shortDescritpion, std::string & synopsis, std::string & description);

private:
  void renderFrame() override;
  void update() override;
  static void resize(GLFWwindow * window, int framebufferWidth, int framebufferHeight);
  CellView * getNeighbourView(int, int);
  void findChanges();
  CellView *getCellView(Cell*);
  void moveUpdate(Direction const d);

private:
  Buffer m_vbo;
  VAO m_vao;
  Program m_program;
  Program m_program_bee;
  CellView backgroundView;
  CellView * beeView;
  CellView winView;
  glm::vec2 beeOrigin{};
  std::vector<CellView *> dataView;
  bool key_pressed;
  int button_pressed;
  Game game;
  glm::vec2 m_offset;
};

#endif // !defined(__PA1_APPLICATION_H__)
