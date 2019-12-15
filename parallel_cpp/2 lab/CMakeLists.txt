cmake_minimum_required(VERSION 3.8)
project(work_01)

set(CMAKE_CXX_STANDARD 17)

add_executable(work_01 main.cpp vector.cpp vector.h)
 
option(JSON_BuildTests OFF)
option(JSON_Install OFF)

add_subdirectory(libs/json)

target_link_libraries(work_01 PRIVATE nlohmann_json::nlohmann_json)

