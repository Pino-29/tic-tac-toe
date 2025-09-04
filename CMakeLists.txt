cmake_minimum_required(VERSION 3.15)
project(tictactoe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
file(GLOB SOURCES
        src/main.cpp
        src/drawable_cell.cpp
        src/drawable_tic_tac_toe_board.cpp
        src/match.cpp
)

add_executable(tictactoe ${SOURCES})

target_include_directories(tictactoe PRIVATE ${PROJECT_SOURCE_DIR}/include)

find_package(SFML 3 REQUIRED COMPONENTS Window Graphics Audio Network)

target_link_libraries(tictactoe PRIVATE SFML::Window SFML::Graphics SFML::Audio SFML::Network)