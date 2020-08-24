INCLUDE(GNUInstallDirs)
ADD_DEFINITIONS("-DGLFW_INCLUDE_NONE")

SET(VOID_SOURCES
    "Core/Application.cpp"
    "Core/Allocator.cpp"
    "Core/Time.cpp"
    "Core/World.cpp"
    "Debug/Log.cpp"
    "ECS/Entity.cpp"
    "Math/Color.cpp"
    "Misc/File.cpp"
    "Misc/ObjLoader.cpp"
    "Input/InputManager.cpp"
    "Rendering/Renderer.cpp"
    "Rendering/Shader.cpp"
    "Rendering/Window.cpp"
    "Rendering/GLAD/GLAD.c"
)

##
## HANDLE OPTIONS
##

ADD_DEFINITIONS("-DVOID_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}")
ADD_DEFINITIONS("-DVOID_VERSION_MINOR=${PROJECT_VERSION_MINOR}")
ADD_DEFINITIONS("-DVOID_VERSION_PATCH=${PROJECT_VERSION_PATCH}")

IF(VOID_ENABLE_DEBUG)
    ADD_DEFINITIONS("-DVOID_ENABLE_DEBUG")
ENDIF()

##
## LINKING DEPENDENCIES
##

PKG_SEARCH_MODULE(OPENGL REQUIRED gl)

ADD_LIBRARY("${CMAKE_PROJECT_NAME}" STATIC ${VOID_SOURCES})
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} PUBLIC
    glfw3
    pthread
    ${OPENGL_LIBRARIES}
)

##
## INSTALLATION
##

INSTALL(
    TARGETS       ${CMAKE_PROJECT_NAME}
    LIBRARY       DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

INSTALL(
    DIRECTORY "."
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/VoidEngine
    FILES_MATCHING
        REGEX   ".*\.hpp$"
        REGEX   ".*\.h$"
)