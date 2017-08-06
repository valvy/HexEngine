PROJECT(PRUT_ENGINE VERSION ${PRUT_ENGINE_VERSION})
IF(APPLE)
	FIND_LIBRARY(COCOA_LIBRARY Cocoa REQUIRED)
	FIND_PACKAGE(OpenGL REQUIRED)
    FIND_LIBRARY(METAL_LIBRARY Metal REQUIRED)
    FIND_LIBRARY(METALKIT_LIBRARY MetalKit REQUIRED)
    FIND_LIBRARY(MODELIO_LIBRARY ModelIO REQUIRED)
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR} ${METAL_INCLUDE_DIR})
  
    SET( 
        PRUT_ENGINE_PLATFORM_SOURCES
        src/platform/apple/MacApp.mm
        src/platform/apple/IOSApp.mm
        src/platform/apple/MetalRenderer.mm
        src/platform/apple/MetalViewController.mm
    )

    SET_SOURCE_FILES_PROPERTIES(
        src/platform/apple/MetalRenderer.mm 
        PROPERTIES COMPILE_FLAGS -fobjc-arc
    )

    SET(
        PRUT_ENGINE_PLATFORM_LIBRARIES
        ${COCOA_LIBRARY}  
        ${METAL_LIBRARY}  
        ${METALKIT_LIBRARY}
        ${MODELIO_LIBRARY}
        ${OPENGL_LIBRARIES}
    )

ENDIF()

SET(PRUT_ENGINE_HEADERS
  ./include/prutengine/AbstractScene.hpp
  ./include/prutengine/Application.hpp
  ./include/prutengine/AssetManager.hpp
  ./include/prutengine/Camera.hpp
  ./include/prutengine/GameObject.hpp
  ./include/prutengine/GraphicsController.hpp
  ./include/prutengine/data/AbstractResource.hpp
  ./include/prutengine/data/GLProgram.hpp
  ./include/prutengine/data/Mesh.hpp
  ./include/prutengine/data/shader.hpp
  ./include/prutengine/data/Texture.hpp
  ./include/prutengine/exceptions/AssetNotLoadedException.hpp
  ./include/prutengine/exceptions/NotYetInitializedException.hpp
  ./include/prutengine/exceptions/PrutEngineException.hpp
  ./include/prutengine/exceptions/RenderingException.hpp
  ./include/prutengine/math/Matrix.hpp
  ./include/prutengine/math/Matrix4x4.hpp
  ./include/prutengine/math/Quaternion.hpp
  ./include/prutengine/math/Utilities.hpp
  ./include/prutengine/math/Vector.hpp
  ./include/prutengine/platform/Input.hpp
  ./include/prutengine/platform/IOSApp.h
  ./include/prutengine/platform/MacApp.h
  ./include/prutengine/platform/MetalRenderer.h
  ./include/prutengine/platform/MetalShaderTypes.h
  ./include/prutengine/platform/MetalViewController.h
  ./include/prutengine/platform/OpenGL.hpp
)

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
    src/GraphicsController.cpp
    src/Mesh.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/RenderingException.cpp
    src/NotYetInitializedException.cpp
    src/AssetNotLoadedException.cpp
)
ADD_DEFINITIONS( "-g -Wall  -O0" )

INCLUDE_DIRECTORIES(${PRUT_ENGINE_SOURCE_DIR}/include )
ADD_LIBRARY(PrutEngine SHARED ${PRUT_ENGINE_SOURCES} ${PRUT_ENGINE_HEADERS} )

TARGET_LINK_LIBRARIES(
    PrutEngine 
    ${PRUT_ENGINE_PLATFORM_LIBRARIES}    
)



