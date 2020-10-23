cmake_minimum_required(VERSION 3.5)

project(PAZI_Jacobi_intersections LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PAZI_Jacobi_intersections main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE akrypt)
