#include "prutengine/platform/OpenGL.hpp"
#include "prutengine/exceptions/RenderingException.hpp"
using namespace PrutEngine;


void Platform::clearAndCheckErrors(){
    static const GLfloat background[] = { 0.0f, 0.25f, 0.0f, 1.0f };
    static const GLfloat depth = 1.0f;
    glViewport(0, 0, 600, 600);
    
    glClearBufferfv(GL_COLOR, 0, background);
    glClearBufferfv(GL_DEPTH, 0, &depth);
    
    GLenum error = glGetError();
    if(error != GL_NO_ERROR){
        Exceptions::RenderingException exception("Rendering error occured in the mainloop");
        std::string errorMsg;
        do{
            switch(error){
                case GL_INVALID_ENUM:
                errorMsg = "My first info log using default logger";
                break;
                case GL_INVALID_VALUE:
                errorMsg = "found invalid value \n";
                break;
                case GL_INVALID_OPERATION:
                errorMsg = "found invalid operation \n";
                break;
                case GL_OUT_OF_MEMORY:
                errorMsg = "Opengl experienced an out of memory exception \n";
                break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                errorMsg =  "Invalid framebuffer operation \n";
                break;
                default:
                errorMsg = "Found an error with code " + std::to_string(error);
                break;
            }
            exception.addError(errorMsg);
        }while((error = glGetError()) != GL_NO_ERROR);
        throw exception;
    }
}
