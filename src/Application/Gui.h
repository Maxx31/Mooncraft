#pragma once

#include "../MCraft.h"

class Gui 
{
public:
  Gui();
  ~Gui();

  static Gui &instance() { return *instancePtr; }

  void update();
  void finalizeFrame();

  Gui(const Gui &) = delete;
  Gui(Gui &&) noexcept = delete;
  Gui(Gui &) = delete;
  Gui &operator=(Gui &) = delete;
  Gui &operator=(Gui &&) noexcept = delete;

private:
  static Gui *instancePtr;
};