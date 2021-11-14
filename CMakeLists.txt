cmake_minimum_required(VERSION 3.15.0)
project(AlienInvaders VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES "lib/*.cpp")
add_library(lib STATIC ${SOURCES})
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

if(WIN32)
    include("windows.h")
endif()

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS}  ${GLEW_INCLUDE_DIRS} include)

add_executable(AlienInvaders main.cpp)

target_link_libraries(AlienInvaders ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} lib)

add_custom_target(CopyShaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
        "${CMAKE_SOURCE_DIR}/res" "${CMAKE_BINARY_DIR}/res"
    COMMENT "Copy res directory to build tree" VERBATIM)

ADD_DEPENDENCIES (AlienInvaders CopyShaders)