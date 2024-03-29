INCLUDE(GNUInstallDirs)
ADD_DEFINITIONS("-DGLFW_INCLUDE_NONE")

SET(LIBRARIES
    "glad"
    "glm"
    "assimp"
)
SET(VOID_SOURCES
    "Core/Application.cpp"
    "Core/Allocator.cpp"
    "Core/Time.cpp"
    "Core/World.cpp"
    "Debug/Log.cpp"
    "Debug/SignalHandler.cpp"
    "ECS/Entity.cpp"
    "Math/Color.cpp"
    "Misc/File.cpp"
    "Misc/ModelLoader.cpp"
    "Misc/Resource.cpp"
    "Misc/Texture.cpp"
    "Input/InputManager.cpp"
    "Rendering/Shader.cpp"
)

##
## HANDLE OPTIONS
##

ADD_DEFINITIONS("-DVOID_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}")
ADD_DEFINITIONS("-DVOID_VERSION_MINOR=${PROJECT_VERSION_MINOR}")
ADD_DEFINITIONS("-DVOID_VERSION_PATCH=${PROJECT_VERSION_PATCH}")

IF(${VOID_ENABLE_OPENGL})
    PKG_SEARCH_MODULE(OPENGL REQUIRED gl)

    SET(VOID_SOURCES
        ${VOID_SOURCES}
        "Platforms/GL/Shader.cpp"
        "Platforms/GL/Window.cpp"
        "Platforms/GL/Renderer.cpp"
    )

    SET(LIBRARIES
        ${LIBRARIES}
        glfw
        ${OPENGL_LIBRARIES}
    )

    ADD_DEFINITIONS("-DVOID_ENABLE_OPENGL")
ENDIF()

##
## LINKING DEPENDENCIES
##

ADD_LIBRARY("${CMAKE_PROJECT_NAME}" STATIC ${VOID_SOURCES})
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} PUBLIC
    ${LIBRARIES}
)
COTIRE("${CMAKE_PROJECT_NAME}")

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
)
