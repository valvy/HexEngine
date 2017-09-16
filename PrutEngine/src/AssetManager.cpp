#include "prutengine/AssetManager.hpp"
#include "prutengine/Application.hpp"
#include "prutengine/exceptions/PrutEngineException.hpp"
#include <unistd.h>
using namespace PrutEngine;
using namespace PrutEngine::Data;



std::vector<GLuint> AssetManager::allPrograms(){
    if(Application::getInstance()->getGraphicsController()->getCurrentGraphicsEngine() == Graphics_Engine::OpenGL){
        std::vector<GLuint> result;
        for(auto it : AssetManager::loadedPrograms){
            auto tmp = static_cast<GLProgram*>(it.get());
            result.push_back(tmp->getProgram());
        }
        return result;
    }
    throw Exceptions::PrutEngineException("Deprecated invalid method called");
}

Data::GraphicsProgram* AssetManager::compileProgram(const std::string& name,const std::vector<std::shared_ptr<Data::Shader>>& shaders) const{
    return Application::getInstance()->getGraphicsController()->compileProgram(name, shaders);
}

std::shared_ptr<Texture> AssetManager::loadTexture(const std::string& path){
    for(auto it : AssetManager::loadedTextures){
        if(it->getDataLocation() == path){
            return it;
        }
    }
    
    auto t = std::shared_ptr<Texture>(new Texture(path));
    loadedTextures.push_back(t);
    return t;
}

std::shared_ptr<Mesh> AssetManager::loadMesh(const std::string& path){
    for(auto it : AssetManager::loadedMeshes){
        if(it->getDataLocation() == path){

            return it;
        }
    }
    
    auto m = std::shared_ptr<Mesh>(new Mesh(path));
    loadedMeshes.push_back(m);
    return m;
    
}

void AssetManager::clear(){
    loadedTextures.clear();
    loadedShaders.clear();
    loadedPrograms.clear();
    loadedMeshes.clear();
}

#ifndef __APPLE__

#define GetCurrentDir getcwd
std::string AssetManager::getAppPath() const{
    char cCurrentPath[FILENAME_MAX];
    
    if(!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        return "Error";
    }
    
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
    
    return cCurrentPath;
}
#endif

std::shared_ptr<Shader> AssetManager::loadShader(const std::string& path,Shader_Types type){
    //Check if the shader already exists
    for(auto it : AssetManager::loadedShaders){
        if(it->getDataLocation() == path){
            return it;
        }
    }
    
    auto sh = std::shared_ptr<Shader>(new Shader(path,type));
    loadedShaders.push_back(sh);
    return sh;
    
}

