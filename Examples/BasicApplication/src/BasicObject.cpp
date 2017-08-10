#include "BasicObject.hpp"
#include <prutengine/Application.hpp>
#include <prutengine/exceptions/PrutEngineException.hpp>
#include <string>
#include <iostream>
#include <utility>

using namespace PrutEngine::Math;

BasicObject::BasicObject(const Vector3f &position) : GameObject(){
    try{
        this->setPosition(position);
        visible = true;
        const std::string path = PrutEngine::Application::getInstance()->getAssetManager()->getAppPath();

    
    const auto graphicsController = PrutEngine::Application::getInstance()->getGraphicsController();//->getCurrentGraphicsEngine();
    
    const std::string mesh = path + "/Assets/Meshes/Hex.obj";
    const std::string texture = path + "/Assets/Textures/cube.bmp";

   
    std::string fragmentShader,vertexShader;
    
    //Setup the shaders of the specific programs
    if( graphicsController->getCurrentGraphicsEngine() == PrutEngine::Graphics_Engine::OpenGL){
        vertexShader = path + "/Assets/Shaders/UnshadedVertex.glsl";
        fragmentShader = path + "/Assets/Shaders/UnshadedFragment.glsl";
    } else if (graphicsController->getCurrentGraphicsEngine() == PrutEngine::Graphics_Engine::AppleMetal){
        vertexShader = "vertexTransform";
        fragmentShader = "fragmentLighting";
    }
 
    auto program = PrutEngine::Application::getInstance()->getAssetManager()->loadProgram(
                    std::make_pair(vertexShader, PrutEngine::Shader_Types::Vertex_Shader),
                              std::make_pair(fragmentShader,PrutEngine::Shader_Types::Fragment_Shader));
    
    
        
    this->setRenderer(graphicsController->createRenderer(mesh, texture, program));
        
    }catch(const PrutEngine::Exceptions::PrutEngineException exception){
        std::cout << "Could not start the program due the following exception: ";
        std::cout << exception.getMsg() << "\n";
        return;
    }
}



void BasicObject::update(float tpf){
   // if(visible){
        GameObject::update(tpf);
        this->rotate(Vector3f(5,90,0), 50.0f * tpf);
    //}
}
