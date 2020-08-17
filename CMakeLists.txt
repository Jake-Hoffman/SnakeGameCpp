project(SnakeGame)
cmake_minimum_required(VERSION 3.7)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/modules)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2TTF REQUIRED)
include_directories(${SDL2TTF_INCLUDE_DIRS})

add_executable(SnakeGame main.cpp gameEngine.cpp snakeGameEngine.cpp window.cpp)
target_link_libraries(SnakeGame ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARY})