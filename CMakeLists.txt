cmake_minimum_required(VERSION 3.5)

project(PAZI_Jacobi_intersections LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PAZI_Jacobi_intersections main.cpp)

add_subdirectory(libakrypt-0.x libakrypt-build)

target_link_libraries(${PROJECT_NAME} PRIVATE akrypt)

# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR} )
