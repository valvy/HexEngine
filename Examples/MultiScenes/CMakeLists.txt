CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
SET (CMAKE_CXX_STANDARD 14)

PROJECT(MULTI_SCENES)

SET(MULTI_SCENES_SOURCES
    ./src/MultiApplication.cpp
    ./src/SceneOne.cpp
    ./src/SceneTwo.cpp
    ./src/BasicObject.cpp
    ./src/Main.cpp
)

SET(MULTI_SCENES_HEADERS
    ./include/MultiApplication.hpp
    ./include/SceneOne.hpp
    ./include/SceneTwo.hpp
    ./include/BasicObject.hpp
)

ADD_EXECUTABLE(
    MultiScenes 
    ${MULTI_SCENES_SOURCES}
    ${MULTI_SCENES_HEADERS}
)


INCLUDE_DIRECTORIES(
    ${PRUT_ENGINE_SOURCE_DIR}/include
    ./include
)

ADD_CUSTOM_COMMAND(
    TARGET MultiScenes POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:MultiScenes>
)

TARGET_LINK_LIBRARIES(
    MultiScenes 
    ${PRUT_ENGINE_BUILD_DIR}
    PrutEngine
)