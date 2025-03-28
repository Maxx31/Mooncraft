#pragma once

// this is to force the formatter to keep the order, because glad must be included first
#if 1
#include <glad/glad.h>
#endif

#define GLM_ENABLE_EXPERIMENTAL

#include <FastNoiseLite.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <lodepng.h>

#include <glm/glm.hpp>
#include <glm/gtc/integer.hpp>
#include <glm/gtx/transform.hpp>

// std libraries
#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <optional>
#include <random>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <span>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

template<typename T>
using SharedRef = std::shared_ptr<T>;

template<typename T>
using WeakRef = std::weak_ptr<T>;

template<typename T>
using UniqueRef = std::unique_ptr<T>;