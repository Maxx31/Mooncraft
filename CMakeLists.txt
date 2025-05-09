cmake_minimum_required(VERSION 3.22.1)
project(MCraft)

set(CMAKE_CXX_STANDARD 23)

if (CMAKE_BUILD_TYPE MATCHES Release)
     set(CMAKE_CXX_FLAGS "-O3")
 elseif (CMAKE_BUILD_TYPE MATCHES Debug)
     set(CMAKE_CXX_FLAGS "-g")
 endif ()

file(GLOB_RECURSE MCraftSources src/*.cpp src/*.h)
 add_executable(MCraft ${MCraftSources})
 target_precompile_headers(MCraft PRIVATE src/MCraft.h)

# glfw
add_subdirectory(third_party/glfw EXCLUDE_FROM_ALL)

# GLAD
add_subdirectory(third_party/GLAD EXCLUDE_FROM_ALL)

# glm
add_subdirectory(third_party/glm EXCLUDE_FROM_ALL)

# imgui
add_library(
        imgui EXCLUDE_FROM_ALL
        third_party/imgui/imgui.cpp
        third_party/imgui/imgui.h
        third_party/imgui/imgui_demo.cpp
        third_party/imgui/imgui_draw.cpp
        third_party/imgui/imgui_internal.h
        third_party/imgui/imgui_widgets.cpp
        third_party/imgui/imstb_rectpack.h
        third_party/imgui/imstb_textedit.h
        third_party/imgui/imstb_truetype.h
        third_party/imgui/imconfig.h
        third_party/imgui/imgui_tables.cpp
        third_party/imgui/backends/imgui_impl_glfw.h
        third_party/imgui/backends/imgui_impl_glfw.cpp
        third_party/imgui/backends/imgui_impl_opengl3.h
        third_party/imgui/backends/imgui_impl_opengl3.cpp
 )
include_directories(imgui third_party/imgui third_party/imgui/backends)

# FastNoiseLite
include_directories(MCraft third_party/FastNoiseLite)

# lodepng
add_library(lodepng EXCLUDE_FROM_ALL third_party/lodepng/lodepng.h third_party/lodepng/lodepng.cpp)
include_directories(lodepng third_party/lodepng)

# link glfw to imgui and link everything to the main app
target_link_libraries(imgui PRIVATE glfw)
target_link_libraries(MCraft PRIVATE glfw glm glad imgui lodepng)

# set a symlink to the assets dir
add_custom_command(
     TARGET MCraft PRE_BUILD COMMAND
    ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)