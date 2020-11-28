cmake_minimum_required(VERSION 3.5)

project(PAZI_Jacobi_intersections LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libakrypt-0.x)

add_executable(curve_test curve_test.cpp my_curves.cpp)
add_executable(sha3_test sha3_test.cpp)

target_link_libraries(curve_test PRIVATE akrypt-shared)
target_link_libraries(sha3_test PRIVATE akrypt-shared)

target_include_directories(curve_test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/libakrypt-0.x/source)
target_include_directories(sha3_test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/libakrypt-0.x/source)
