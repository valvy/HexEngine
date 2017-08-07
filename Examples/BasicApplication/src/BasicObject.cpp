#include "BasicObject.hpp"
#include <prutengine/Application.hpp>
#include <string>
#include <utility>

using namespace PrutEngine::Math;

BasicObject::BasicObject(const Vector3f &position) : GameObject(){
    
    this->setPosition(position);
    visible = true;
    const std::string path = PrutEngine::Application::getInstance()->getAssetManager()->getAppPath();

    this->loadMesh(path + "/Assets/Meshes/Hex.obj");
    
    this->loadProgram(
                    std::make_pair(path + "/Assets/Shaders/UnshadedVertex.glsl",GL_VERTEX_SHADER),
                    std::make_pair(path + "/Assets/Shaders/UnshadedFragment.glsl",GL_FRAGMENT_SHADER));
    this->loadTexture(path + "/Assets/Textures/cube.bmp");
}



void BasicObject::update(float tpf){
   // if(visible){
        GameObject::update(tpf);
        this->rotate(Vector3f(5,90,0), 50.0f * tpf);
    //}
}
