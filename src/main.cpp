
#include "Application/Application.h"
#include "MCraft.h"

int main() 
{
  Application &app = Application::instance();

  app.setScene(std::make_shared<Scene>());

  return app.run();
}
