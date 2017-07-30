#ifndef OPENGL_HPP
#define OPENGL_HPP

#ifdef __APPLE__
#include <OpenGl/gl3.h>
#include <OpenGL/gl3ext.h>
#endif

#ifdef __linux__
#include <GL/glew.h>
#include <GL/glx.h>
#endif

#endif
