#include "prutengine/Application.hpp"
#include "prutengine/platform/OpenGL.hpp"

#include "prutengine/math/Matrix4x4.hpp"
#include "prutengine/math/Utilities.hpp"
#include "prutengine/platform/Input.hpp"
#include "prutengine/exceptions/RenderingException.hpp"
#include "prutengine/exceptions/NotYetInitializedException.hpp"



using namespace PrutEngine;

	std::ostream& operator<<(std::ostream& out, const Graphics_Engine value){
		switch(value){
			case Graphics_Engine::AppleMetal:
			out << std::string("Apple Metal");
			break;
			default:
			out << std::string("OpenGL");
			break;
		}
		return out;
	}

Application* Application::instance;

void Application::setInstance(Application* app){
    Application::instance = app;
    //instance->start();
}

Application::~Application(){
    
}

Application::Application(){

}

std::shared_ptr<AssetManager> Application::getAssetManager(){
    if(this->assetManager == nullptr){
        this->assetManager = std::shared_ptr<AssetManager>(new AssetManager());
    }
    return this->assetManager;
}

void Application::loadScene(std::shared_ptr<AbstractScene> scene){
    this->currentScene = scene;
}

void Application::awake(){
    this->currentScene->awake();
}

Application* Application::getInstance(){
	if(instance == nullptr){
      throw Exceptions::NotYetInitializedException("Instance is null");
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



void Application::update(){
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
         exception.addError(errorMsg);
        }while((error = glGetError()) != GL_NO_ERROR);
        throw exception;
    }

	currentScene->update(time_per_frame);
    

    this->time_per_frame = 0.00001f * (clock() - timer);
  
}
