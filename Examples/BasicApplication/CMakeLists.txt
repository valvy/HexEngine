CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
SET (CMAKE_CXX_STANDARD 14)

PROJECT(BASIC_APPLICATION)

SET(BASIC_APPLICATION_SOURCES
    src/BasicApplication.cpp
    src/BasicObject.cpp
    src/BasicScene.cpp
    src/Main.cpp
)

SET(BASIC_APPLICATION_HEADERS
    ./include/BasicApplication.hpp
    ./include/BasicObject.hpp
    ./include/BasicScene.hpp
)

IF(APPLE)
    SET(BASIC_APPLICATION_METAL_SHADERS
        src/Shaders.metal
    ) 

  
SET_SOURCE_FILES_PROPERTIES(
    src/Shaders.metal
    PROPERTIES LANGUAGE C++
)
ENDIF()








INCLUDE_DIRECTORIES( ${METAL_INCLUDE_DIR})
ADD_EXECUTABLE(
    BasicApplication 
    ${BASIC_APPLICATION_SOURCES}
    ${BASIC_APPLICATION_HEADERS}
    ${BASIC_APPLICATION_METAL_SHADERS}
)

#set_target_properties(
#    BasicApplication 
#    PROPERTIES XCODE_ATTRIBUTE$<METAL_COMPILER>"/")

INCLUDE_DIRECTORIES(
    ${PRUT_ENGINE_SOURCE_DIR}/include
    ./include
)
ADD_CUSTOM_COMMAND(
    TARGET BasicApplication POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:BasicApplication>
)

TARGET_LINK_LIBRARIES(
    BasicApplication 
    ${PRUT_ENGINE_BUILD_DIR}
    PrutEngine
)