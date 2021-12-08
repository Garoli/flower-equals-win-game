#define GLM_FORCE_SWIZZLE
#include "FlowerApplication.hpp"

int main(int /*argc*/, char * /*argv*/[])
{
  FlowerApplication app(640, 480);
  app.setCallbacks();
  app.mainLoop();
  return 0;
}
