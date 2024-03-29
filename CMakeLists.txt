##
## PREAMBLE
##

CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
FIND_PACKAGE(PkgConfig REQUIRED)

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_FIND_LIBRARY_SUFFIXES .a)
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})
INCLUDE(cotire)

##
## BUILD OPTIONS
##

OPTION(VOID_BUILD_EXAMPLES  "Build VoidEngine examples."         TRUE)
OPTION(VOID_ENABLE_OPENGL   "Enable OpenGL backend"              TRUE)

IF(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    MESSAGE(STATUS "Setting build type to 'Debug' as none was specified.")
    SET(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
ENDIF()

MESSAGE(STATUS "Building library as ${CMAKE_BUILD_TYPE}")
MESSAGE(STATUS "Building with OpenGL backend: ${VOID_ENABLE_OPENGL}")

##
## PROJECT
##

PROJECT(
    "void"
    VERSION 0.1.0
    DESCRIPTION "A dumb-ass game engine."
    LANGUAGES C CXX
)

##
## GLAD OPTIONS
##

SET(GLAD_PROFILE    "core"   CACHE STRING "" FORCE)
SET(GLAD_API        "gl=4.5" CACHE STRING "" FORCE)
SET(GLAD_GENERATOR  "c"      CACHE STRING "" FORCE)
SET(GLAD_SPEC       "gl"     CACHE STRING "" FORCE)
SET(GLAD_REPRODUCABLE ON     CACHE BOOL   "" FORCE)
SET(GLAD_EXTENSIONS 
    "GL_ARB_debug_output"
    CACHE STRING "" FORCE)

ADD_SUBDIRECTORY(ThirdParty/glad/)

##
## GLFW
##

SET(BUILD_SHARED_LIBS   OFF CACHE BOOL "" FORCE)
SET(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
SET(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
SET(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
SET(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
ADD_SUBDIRECTORY(ThirdParty/glfw/)

##
## GLM
##

SET(GLM_TEST_ENABLE     OFF CACHE BOOL "" FORCE)
SET(BUILD_SHARED_LIBS   OFF CACHE BOOL "" FORCE)
SET(BUILD_STATIC_LIBS   ON  CACHE BOOL "" FORCE)
ADD_SUBDIRECTORY(ThirdParty/glm/)

##
## ASSIMP
##

SET(BUILD_SHARED_LIBS         OFF CACHE BOOL "" FORCE)
SET(ASSIMP_BUILD_TESTS        OFF CACHE BOOL "" FORCE)
SET(ASSIMP_INSTALL            OFF CACHE BOOL "" FORCE)
SET(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
ADD_SUBDIRECTORY(ThirdParty/assimp/)
INCLUDE_DIRECTORIES(ThirdParty/assimp/include)

##
## VOID ENGINE
##

ADD_SUBDIRECTORY(VoidEngine)

IF(VOID_BUILD_EXAMPLES)
    ADD_SUBDIRECTORY(Examples)
ENDIF()
