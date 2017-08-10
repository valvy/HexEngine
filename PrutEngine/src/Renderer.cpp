#include "prutengine/Renderer.hpp"

using namespace PrutEngine;

Renderer::~Renderer(){
    
}

std::shared_ptr<Data::Mesh> Renderer::getMesh() const{
    return this->mesh;
}


std::shared_ptr<Data::GraphicsProgram> Renderer::getProgram() const{
    return this->program;
}

std::shared_ptr<Data::Texture> Renderer::getTexture() const{
    return this->texture;
}


GLRenderer::~GLRenderer(){
    
}
