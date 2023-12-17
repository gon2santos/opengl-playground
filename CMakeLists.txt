cmake_minimum_required(VERSION 3.7)

project(chip_eight_emu VERSION 0.1.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2 and SDL2_image
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(CHIP_eight_emulator ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Set the source files
set(SOURCES 
    ./src/main.cpp
    ./src/include/Game.hpp
    ./src/include/Game.cpp
)

# Add an executable target
add_executable(main ${SOURCES})
target_link_libraries(main ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})



