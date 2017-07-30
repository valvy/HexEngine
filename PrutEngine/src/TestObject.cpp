#include "prutengine/deprecated/TestObject.hpp"
#include "prutengine/Application.hpp"
#include "prutengine/platform/OpenGL.hpp"
#include <string>
#include <utility>
#include <iostream>

using namespace PrutEngine;
using namespace PrutEngine::Math;

TestObject::TestObject(const Vector3<float> &position) : GameObject(){
    
    this->setPosition(position);
    visible = true;
    const std::string path = Application::getInstance()->getAppPath();
    this->loadMesh(path + "/Assets/Meshes/Hex.obj");
    
    this->loadProgram(
                    std::make_pair(path + "/Assets/Shaders/UnshadedVertex.glsl",GL_VERTEX_SHADER),
                    std::make_pair(path + "/Assets/Shaders/UnshadedFragment.glsl",GL_FRAGMENT_SHADER));
    this->loadTexture(path + "/Assets/Textures/cube.bmp");
}

void TestObject::update(float tpf){
   // if(visible){
        GameObject::update(tpf);
    //}
}
