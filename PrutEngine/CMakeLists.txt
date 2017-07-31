PROJECT(PRUT_ENGINE VERSION ${PrutEngine_version})

SET(
    PRUT_ENGINE_SOURCES
    src/AbstractResource.cpp
    src/AbstractScene.cpp
    src/Application.cpp
    src/AssetManager.cpp
    src/Camera.cpp
    src/GameObject.cpp
    src/GLProgram.cpp
    src/MacApp.mm
    src/Mesh.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/RenderingException.cpp
    src/NotYetInitializedException.cpp
    src/AssetNotLoadedException.cpp
)
ADD_DEFINITIONS( "-g -Wall   -O0" )

include_directories(${PRUT_ENGINE_SOURCE_DIR}/include )
add_library(PrutEngine SHARED ${PRUT_ENGINE_SOURCES} )



if(APPLE)
	FIND_LIBRARY(COCOA_LIBRARY Cocoa)
	FIND_PACKAGE(OpenGL REQUIRED)
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
	TARGET_LINK_LIBRARIES(PrutEngine ${COCOA_LIBRARY} ${OPENGL_LIBRARIES})
else()

endif()