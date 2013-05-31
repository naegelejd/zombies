cmake_minimum_required(VERSION 2.8)

project(game)

set(CMAKE_BUILD_TYPE Debug)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# (system, window, graphics, network, audio, main)
find_package(SFML COMPONENTS system graphics window)

add_subdirectory(ext)

include_directories(${SFML_INCLUDE_DIR} ${LUA_INCLUDE_DIR})

add_executable(game
    Main.cpp
    Game.cpp
    LoadState.cpp
    MainMenuState.cpp
    PlayState.cpp
    Button.cpp
    Configurator.cpp
    Resourcer.cpp
    Inputter.cpp
    Player.cpp
    Zombie.cpp
    Flock.cpp)

target_link_libraries(game ${SFML_LIBRARIES} lua)
