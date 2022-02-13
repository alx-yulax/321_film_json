cmake_minimum_required(VERSION 3.21)
project(321_film_json)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)

add_executable(321_film_json main.cpp)

target_link_libraries(321_film_json PRIVATE nlohmann_json::nlohmann_json)