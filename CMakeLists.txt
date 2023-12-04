cmake_minimum_required(VERSION 3.7)
project(sdl_demo VERSION 0.1.0 LANGUAGES C CXX)

find_package(SDL2 REQUIRED)
include_directories(sdl_demo ${SDL2_INCLUDE_DIRS})

add_executable(sdl_demo ./src/main.cpp)
target_link_libraries(sdl_demo ${SDL2_LIBRARIES})



