#include "prutengine/Renderer.hpp"

using namespace PrutEngine;

Renderer::~Renderer(){
    
}

void Renderer::set(const std::string& mesh, const std::string& texture, std::shared_ptr<Data::GraphicsProgram> program){
    const auto assetManager =  Application::getInstance()->getAssetManager();
    this->program = program;
    this->mesh = assetManager->loadMesh(mesh);
    this->texture = assetManager->loadTexture(texture);
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

GLRenderer::GLRenderer(const std::string& mesh, const std::string& texture, std::shared_ptr<Data::GraphicsProgram> program){
    const Data::GLProgram* progr = static_cast<Data::GLProgram*>(program.get());
    this->pos_reference = glGetUniformLocation(progr->getProgram(), "mv_matrix");
    this->set(mesh,texture,program);
}

GLint GLRenderer::getPositionRef() const{
    return this->pos_reference;
}
