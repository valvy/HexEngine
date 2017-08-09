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

    this->loadMesh(path + "/Assets/Meshes/Hex.obj");
    
    const auto graphicsEngine = PrutEngine::Application::getInstance()->getGraphicsController()->getCurrentGraphicsEngine();
    
    std::string fragmentShader,vertexShader;
    
    //Setup the shaders of the specific programs
    if( graphicsEngine == PrutEngine::Graphics_Engine::OpenGL){
        vertexShader = path + "/Assets/Shaders/UnshadedVertex.glsl";
        fragmentShader = path + "/Assets/Shaders/UnshadedFragment.glsl";
    } else if (graphicsEngine == PrutEngine::Graphics_Engine::AppleMetal){
        vertexShader = "vertexTransform";
        fragmentShader = "fragmentLighting";
    }
   
    //std::cout << vertexShader << "\n";
    
    this->loadProgram(
                    std::make_pair(vertexShader, PrutEngine::Shader_Types::Vertex_Shader),
                    std::make_pair(fragmentShader,PrutEngine::Shader_Types::Fragment_Shader)
    );
    
    this->loadTexture(path + "/Assets/Textures/cube.bmp");
    
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
