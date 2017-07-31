cmake_minimum_required (VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)

PROJECT(BASIC_APPLICATION)

SET(BASIC_APPLICATION_SOURCES
    src/BasicApplication.cpp
    src/BasicObject.cpp
    src/BasicScene.cpp
    src/Main.cpp
)

add_executable(BasicApplication ${BASIC_APPLICATION_SOURCES})
include_directories(
    ${PRUT_ENGINE_SOURCE_DIR}/include
    ./include
)

add_custom_command(TARGET BasicApplication POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:BasicApplication>)

target_link_libraries(BasicApplication ${PRUT_ENGINE_BUILD_DIR} PrutEngine)