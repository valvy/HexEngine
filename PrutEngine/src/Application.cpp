#include "prutengine/Application.hpp"
#include "prutengine/deprecated/TestScene.hpp"
#include "prutengine/platform/OpenGL.hpp"
#include "prutengine/AssetManager.hpp"
#include "prutengine/math/Matrix4x4.hpp"
#include "prutengine/math/Utilities.hpp"
#include "prutengine/platform/Input.hpp"
#include "prutengine/exceptions/RenderingException.hpp"
#include "easylogging++.h"


using namespace PrutEngine;

std::shared_ptr<Application> Application::instance;



void Application::start(){
    this->currentScene = std::unique_ptr<AbstractScene>(new TestScene());
}

Application::Application(){
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

std::shared_ptr<Application> Application::getInstance(){
	if(instance == nullptr){
		instance = std::shared_ptr<Application>(new Application());
        instance->start();//Make sure the gameobjects in the application can use this pointer
	}
	return instance;
}



void Application::keyDown(unsigned short keyCode){
    if(keyCode == KeyCodes::ESCAPE_KEY){
        this->quit();
    }else{
        this->currentScene->keyDown(keyCode);
    }
}



void Application::loop(){
    clock_t timer;
    timer = clock();
    
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
         LOG(WARNING) << errorMsg;
         exception.addError(errorMsg);
        }while((error = glGetError()) != GL_NO_ERROR);
        throw exception;
    }

	currentScene->update(time_per_frame);
    

    this->time_per_frame = 0.00001f * (clock() - timer);
  
}
