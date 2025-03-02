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
  void update();
  void finalizeFrame();

  ~Gui();
};
