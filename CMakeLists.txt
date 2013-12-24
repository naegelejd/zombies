cmake_minimum_required(VERSION 2.8)

project(zombies)

set(CMAKE_BUILD_TYPE Debug)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# (system, window, graphics, network, audio, main)
find_package(SFML COMPONENTS system graphics audio window)

add_subdirectory(ext)

include_directories(${SFML_INCLUDE_DIR} ${LUA_INCLUDE_DIR})

add_executable(zombies
    main.cpp
    game.cpp
    configurator.cpp
    resourcer.cpp
    system.cpp
    #player.cpp
    #zombie.cpp
    #flock.cpp)
)

target_link_libraries(zombies ${SFML_LIBRARIES} lua)
