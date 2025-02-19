cmake_minimum_required(VERSION 3.10)
project(DiamondSquareTerrain VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCES
        source.cpp
        DiamondSquareAlgorithm.cpp
        Renderer3D.cpp
)

set(HEADERS
        datatypes.h
        Renderer3D.h
        DiamondSquareAlgorithm.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
