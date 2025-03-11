#pragma once
#include "../MCraft.h"

class Gui {
  Gui();

public:
  Gui(const Gui &) = delete;
  Gui(Gui &&) = delete;
  Gui(Gui &) = delete;

  static Gui &instance() {
    static Gui gui;
    return gui;
  }

  static void update();
  static void finalizeFrame();

  ~Gui();
};
