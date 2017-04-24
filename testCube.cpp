#include "testCube.hpp"
#include "Application.hpp"
#include "OpenGL.hpp"
#include <string>
#include <utility>
#include <iostream>
TestCube::TestCube(const Vector3<float> &position) : GameObject(){
    
    this->setPosition(position);
    
    const std::string path = Application::getInstance()->getAppPath();
    this->loadMesh(path + "/Assets/Meshes/Hex.obj");
    this->loadTexture( path + "/Assets/Textures/Clouds.bmp");
    this->loadProgram(
                    std::make_pair(path + "/Assets/Shaders/UnshadedVertex.glsl",GL_VERTEX_SHADER),
                    std::make_pair(path + "/Assets/Shaders/UnshadedFragment.glsl",GL_FRAGMENT_SHADER));
}

void TestCube::update(float tpf){
    GameObject::update(tpf);
}
