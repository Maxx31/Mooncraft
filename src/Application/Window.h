#pragma once

class Window {

  const char *name = "MoonCraft";
  int windowWidth = 800;
  int windowHeight = 600;
  GLFWwindow *window = nullptr;
  glm::vec4 clearColor = {0.25f, 0.62f, 0.78f, 1};

  Window();

  void setupCallbacks();
  static bool setupGlad();

  static void onKeyEvent(GLFWwindow *window, int32_t key, int32_t scancode, int32_t action, int32_t mode);
  static void onResized(GLFWwindow *window, int32_t width, int32_t height);
  static void onMouseButtonEvent(GLFWwindow *window, int32_t button, int32_t action, int32_t mods);
  static void onRefreshWindow(GLFWwindow *window);
  static void onWindowError(int errorCode, const char *description);
  static void onOpenGlMessage(GLenum source,
                              GLenum type,
                              GLuint id,
                              GLenum severity,
                              GLsizei length,
                              const GLchar *message,
                              const void *userParam);

public:
  Window(const Window &) = delete;
  Window(Window &) = delete;
  Window(Window &&) = delete;

  [[nodiscard]] int getWindowWidth() const { return windowWidth; }
  void setWindowWidth(int windowWidth) { Window::windowWidth = windowWidth; }

  [[nodiscard]] int getWindowHeight() const { return windowHeight; }
  void setWindowHeight(int windowHeight) { Window::windowHeight = windowHeight; }

  [[nodiscard]] GLFWwindow *getContext() { return window; };

  static Window &instance() {
    static Window window;
    return window;
  }
  bool isValid() { return window != nullptr; };
  [[nodiscard]] bool shouldClose() const { return glfwWindowShouldClose(window); };
  void update();
  void finalizeFrame();

  ~Window();

  void pollEvents();
};
