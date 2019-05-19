cmake_minimum_required(VERSION 3.14)
project(wars)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_MODULE_PATH "/usr/share/cmake/Modules")

link_directories(SFML_LIBRARY_DIR SFGUI_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR SFGUI_INCLUDE_DIR)

find_package(SFML 2.5.1 REQUIRED COMPONENTS system window graphics network audio)
find_package(SFGUI 0.3.1 REQUIRED)

add_executable(wars src/main.cpp)
target_link_libraries(wars sfml-graphics sfml-window sfml-system ${SFGUI_LIBRARY})