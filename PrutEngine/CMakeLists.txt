PROJECT(Engine VERSION ${PrutEngine_version})

SET(
    ENGINE_SOURCES
    src/AbstractResource.cpp
    src/AbstractScene.cpp
    src/Application.cpp
    src/AssetManager.cpp
    src/Camera.cpp
    src/GameCam.cpp
    src/GameObject.cpp
    src/GLProgram.cpp
    src/Hex.cpp
    src/HexGameScene.cpp
    src/MacApp.mm
    src/Mesh.cpp
    src/Shader.cpp
    src/TestCube.cpp
    src/Texture.cpp
)

include_directories(${Engine_SOURCE_DIR}/include )
add_executable(PrutEngine ${ENGINE_SOURCES} )

add_custom_command(TARGET PrutEngine POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:PrutEngine>)

if(APPLE)
	FIND_LIBRARY(COCOA_LIBRARY Cocoa)
	FIND_PACKAGE(OpenGL REQUIRED)
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
	TARGET_LINK_LIBRARIES(PrutEngine ${COCOA_LIBRARY} ${OPENGL_LIBRARIES})
else()

endif()