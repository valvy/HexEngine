#ifndef PRUTENGINE_OPENGL_HPP
#define PRUTENGINE_OPENGL_HPP

#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#elif TARGET_OS_IPHONE
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#elif TARGET_OS_MAC
#include <OpenGl/gl3.h>
#include <OpenGL/gl3ext.h>
#endif
#endif



#ifdef __linux__
#include <GL/glew.h>
#include <GL/glx.h>
#endif


namespace PrutEngine{
    namespace Platform{
        void clearAndCheckErrors();
        
        
    }
}



#endif
