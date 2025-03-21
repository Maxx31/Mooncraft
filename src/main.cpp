#include "Application/Application.h"
#include "MCraft.h"

int main(int argc, char **argv) 
{
  std::string savePath = argc > 1 ? argv[1] : "default.glc";

  Application &app = Application::CreateOrGetApplication();
  app.setScene(std::make_shared<Scene>(savePath));
  int32_t appReturnCode = app.run();

  Application::DestroyApplication(); 
  return appReturnCode;
}