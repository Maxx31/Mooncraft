
#include "Application/Application.h"
#include "MCraft.h"

int main() 
{
  Application &app = Application::instance();
  SharedRef<Scene> scene = std::make_shared<Scene>();
  app.setScene(scene);

  return app.run();
}
