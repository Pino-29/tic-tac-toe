cmake_minimum_required(VERSION 3.15)
project(tic_tac_toe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
file(GLOB SOURCES src/*.cpp)

add_executable(tic_tac_toe ${SOURCES})

target_include_directories(tic_tac_toe PRIVATE ${PROJECT_SOURCE_DIR}/include)