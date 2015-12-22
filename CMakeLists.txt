cmake_minimum_required(VERSION 3.3)
project(the-lair-of-the-minotaur)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include(ExternalProject)

# Set default ExternalProject root directory
set_directory_properties(PROPERTIES EP_PREFIX ${PROJECT_SOURCE_DIR}/libs)

ExternalProject_Add(
        lodepng-master
        SOURCE_DIR ${PROJECT_SOURCE_DIR}/libs/lodepng
        DOWNLOAD_DIR ${PROJECT_SOURCE_DIR}/libs/download
        URL https://github.com/lvandeve/lodepng/archive/master.zip
        INSTALL_COMMAND ""
        PATCH_COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/makefiles/lodepng-CMakeLists.txt" ${PROJECT_SOURCE_DIR}/libs/lodepng/CMakeLists.txt
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        LOG_BUILD ON)

set(LODEPNG_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/libs/lodepng)
set(LODEPNG_LIBRARY_PATH ${PROJECT_SOURCE_DIR}/libs/lodepng/lib/${CMAKE_FIND_LIBRARY_PREFIXES}lodepng.a)
set(LODEPNG_LIBRARY lodepng)

add_library(${LODEPNG_LIBRARY} UNKNOWN IMPORTED)
set_property(TARGET ${LODEPNG_LIBRARY} PROPERTY IMPORTED_LOCATION ${LODEPNG_LIBRARY_PATH})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${LODEPNG_INCLUDE_DIR})

set(SOURCE_FILES
        source/game.cpp
        source/pathfinding/pathfinding_graph.cpp
        source/pathfinding/pathfinding_graph.h
        source/math/vector2.cpp
        source/math/vector2.h
        source/pathfinding/binary_heap.h
        source/pathfinding/comparator.h
        source/pathfinding/pathfinding_node.cpp
        source/pathfinding/pathfinding_node.h
        source/pathfinding/pathfinding_node_comparator.cpp
        source/pathfinding/pathfinding_node_comparator.h
        source/tile_map.cpp
        source/tile_map.h
        source/gameobject/game_object.cpp
        source/gameobject/game_object.h
        source/gameobject/simple_game_object.cpp
        source/gameobject/simple_game_object.h
        source/asset_manager.cpp
        source/asset_manager.h
        source/image.h
        source/animation/animation_state.h
        source/animation/attacking.cpp
        source/animation/attacking.h
        source/animation/dying.cpp
        source/animation/dying.h
        source/animation/idle.cpp
        source/animation/idle.h
        source/animation/running.cpp
        source/animation/running.h
        source/gameobject/game_object_drawer.cpp
        source/gameobject/game_object_drawer.h
        source/opengl_extensions/pixel_2_world.cpp
        source/opengl_extensions/pixel_2_world.h
        source/enemy.cpp source/enemy.h
        source/player.cpp source/player.h source/directions.cpp source/directions.h source/enemy_manager.cpp source/enemy_manager.h source/opengl_extensions/text.cpp source/opengl_extensions/text.h)

add_executable(the-lair-of-the-minotaur ${SOURCE_FILES})

add_dependencies(the-lair-of-the-minotaur lodepng-master)

target_link_libraries(the-lair-of-the-minotaur ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${LODEPNG_LIBRARY} -luuid)