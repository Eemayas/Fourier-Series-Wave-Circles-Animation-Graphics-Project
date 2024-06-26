cmake_minimum_required(VERSION 3.10)

# Required version of cpp
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project("Graphics_Project" VERSION 0.1 LANGUAGES CXX C)

message(STATUS "The build type is set as ${CMAKE_BUILD_TYPE}.")
# set build type as debug
if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# create a list to keep source files in a place

# Source files
set(SOURCES
    src/Fourier\ Seriess/main.cpp
    src/Fourier\ Seriess/draw.cpp
    src/Fourier\ Seriess/utils.cpp
    src/Fourier\ Seriess/constant.cpp
)

# Header files
set(HEADERS
    include/draw.h
    include/utils.h
)





# Executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})



find_package(OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS})

target_include_directories("${PROJECT_NAME}" PUBLIC "${PROJECT_BINARY_DIR}" PUBLIC include)

add_subdirectory("./lib")

target_link_libraries("${PROJECT_NAME}" ${OPENGL_LIBRARIES} 
                OpenGL::GL
                glfw 
                glad )


set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)


