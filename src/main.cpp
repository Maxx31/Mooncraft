
#include "Application/Application.h"
#include "MCraft.h"

int main() 
{
  std::cout << "Hello World from MCraft!" << std::endl;

  Application &app = Application::instance();
  Scene scene = Scene();
  app.setScene(scene);

  return app.run();
}
