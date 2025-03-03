#pragma once
// this is to force the formatter to keep the order
#if 1
#include <glad/glad.h>
#endif

#define GLM_ENABLE_EXPERIMENTAL

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <lodepng.h>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

template<typename T>
using SharedRef = std::shared_ptr<T>;

template<typename T>
using WeakRef = std::weak_ptr<T>;

template<typename T>
using Scoped = std::unique_ptr<T>;
