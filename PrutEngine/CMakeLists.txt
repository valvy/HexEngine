PROJECT(PRUT_ENGINE VERSION ${PRUT_ENGINE_VERSION})
IF(APPLE)
	FIND_LIBRARY(COCOA_LIBRARY Cocoa REQUIRED)
	FIND_PACKAGE(OpenGL REQUIRED)
    FIND_LIBRARY(METAL_LIBRARY Metal REQUIRED)
    FIND_LIBRARY(METALKIT_LIBRARY MetalKit REQUIRED)
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR} ${METAL_INCLUDE_DIR})
  
    SET( 
        PRUT_ENGINE_PLATFORM_SOURCES
        src/platform/apple/MacApp.mm
        src/platform/apple/IOSApp.mm
    )

    SET(
        PRUT_ENGINE_PLATFORM_LIBRARIES
        ${COCOA_LIBRARY}  
        ${METAL_LIBRARY}  
        ${METALKIT_LIBRARY}
        ${OPENGL_LIBRARIES}
    )

ENDIF()

SET(
    PRUT_ENGINE_SOURCES
    ${PRUT_ENGINE_PLATFORM_SOURCES}
    src/AbstractResource.cpp
    src/AbstractScene.cpp
    src/Application.cpp
    src/AssetManager.cpp
    src/Camera.cpp
    src/GameObject.cpp
    src/GLProgram.cpp
    src/Mesh.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/RenderingException.cpp
    src/NotYetInitializedException.cpp
    src/AssetNotLoadedException.cpp
)
ADD_DEFINITIONS( "-g -Wall  -O0" )

INCLUDE_DIRECTORIES(${PRUT_ENGINE_SOURCE_DIR}/include )
ADD_LIBRARY(PrutEngine SHARED ${PRUT_ENGINE_SOURCES} )

TARGET_LINK_LIBRARIES(
    PrutEngine 
    ${PRUT_ENGINE_PLATFORM_LIBRARIES}    
)



