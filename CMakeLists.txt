cmake_minimum_required(VERSION 3.10)
project(mwe_grid_font)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(glfw3)
find_package(glad)
find_package(glm)
find_package(fmt)
target_link_libraries(${PROJECT_NAME} glfw glad::glad glm::glm fmt::fmt)
