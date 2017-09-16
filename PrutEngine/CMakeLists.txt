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
        src/platform/apple/MetalRenderer.mm
        src/platform/apple/MetalViewController.mm
        src/platform/apple/AppDelegate.mm
        src/platform/apple/AbstractWindow.mm
        src/platform/apple/OpenGLWindow.mm
        src/platform/apple/Miscellaneous.mm
        src/platform/apple/MetalWindow.mm
    )

    SET_SOURCE_FILES_PROPERTIES(
        ${PRUT_ENGINE_PLATFORM_SOURCES}
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

    SET(
        PRUT_ENGINE_PLATFORM_HEADERS
        ./include/prutengine/platform/apple/AbstractWindow.h
        ./include/prutengine/platform/apple/AppDelegate.h
        #./include/prutengine/platform/apple/MacApp.h
        ./include/prutengine/platform/apple/MetalWindow.h
        ./include/prutengine/platform/apple/MetalRenderer.h
        ./include/prutengine/platform/apple/MetalShaderTypes.h
        ./include/prutengine/platform/apple/MetalViewController.h
        ./include/prutengine/platform/apple/OpenGLWindow.h
    )
ELSEIF(UNIX)#Linux check
    FIND_PACKAGE(OpenGL REQUIRED)
    FIND_PACKAGE(X11 REQUIRED)
    FIND_PACKAGE(GLEW REQUIRED)

    INCLUDE_DIRECTORIES(
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
    )

    SET( 
        PRUT_ENGINE_PLATFORM_SOURCES
        ./src/platform/gnu_linux/GnuXApp.cpp
    )

    SET(
        PRUT_ENGINE_PLATFORM_LIBRARIES
        ${GLEW_LIBRARIES} 
        ${OPENGL_LIBRARIES} 
        ${X11_LIBRARIES}
    )

ENDIF()



SET(PRUT_ENGINE_HEADERS
    ${PRUT_ENGINE_PLATFORM_HEADERS}
    ./include/prutengine/AbstractScene.hpp
    ./include/prutengine/Application.hpp
    ./include/prutengine/AssetManager.hpp
    ./include/prutengine/Camera.hpp
    ./include/prutengine/GameObject.hpp
    ./include/prutengine/GraphicsController.hpp
    ./include/prutengine/data/AbstractResource.hpp
    ./include/prutengine/data/GraphicsProgram.hpp
    ./include/prutengine/data/Mesh.hpp
    ./include/prutengine/data/Shader.hpp
    ./include/prutengine/data/Texture.hpp
    ./include/prutengine/exceptions/AssetNotLoadedException.hpp
    ./include/prutengine/Renderer.hpp
    ./include/prutengine/Transform.hpp
    ./include/prutengine/exceptions/NotYetInitializedException.hpp
    ./include/prutengine/exceptions/PrutEngineException.hpp
    ./include/prutengine/exceptions/RenderingException.hpp
    ./include/prutengine/exceptions/InitializationException.hpp
    ./include/prutengine/math/Matrix.hpp
    ./include/prutengine/math/Matrix4x4.hpp
    ./include/prutengine/math/Quaternion.hpp
    ./include/prutengine/math/Utilities.hpp
    ./include/prutengine/math/Vector.hpp
    ./include/prutengine/platform/Input.hpp
    
    ./include/prutengine/platform/OpenGL.hpp
    
)

SET(
    PRUT_ENGINE_SOURCES
    ${PRUT_ENGINE_PLATFORM_SOURCES}
    src/data/AbstractResource.cpp
    src/AbstractScene.cpp
    src/Application.cpp
    src/AssetManager.cpp
    src/Camera.cpp
    src/GameObject.cpp
    src/data/GraphicsProgram.cpp
    src/GraphicsController.cpp
    src/data/Mesh.cpp
    src/data/Shader.cpp
    src/data/Texture.cpp
    src/exceptions/RenderingException.cpp
    src/exceptions/NotYetInitializedException.cpp
    src/exceptions/AssetNotLoadedException.cpp
    src/exceptions/InitializationException.cpp
    src/platform/OpenGL.cpp
    src/Renderer.cpp
    src/Transform.cpp
)
ADD_DEFINITIONS( "-g -Wall  -O0" )

INCLUDE_DIRECTORIES(${PRUT_ENGINE_SOURCE_DIR}/include )
ADD_LIBRARY(PrutEngine SHARED ${PRUT_ENGINE_SOURCES} ${PRUT_ENGINE_HEADERS} )

TARGET_LINK_LIBRARIES(
    PrutEngine 
    ${PRUT_ENGINE_PLATFORM_LIBRARIES}    
)



