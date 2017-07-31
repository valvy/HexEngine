#include "prutengine/AssetManager.hpp"
#include <iostream>

using namespace PrutEngine;
using namespace PrutEngine::Data;



std::vector<GLuint> AssetManager::allPrograms(){
    std::vector<GLuint> result;
    for(auto it : AssetManager::loadedPrograms){
        result.push_back(it->getProgram());
    }
    return result;
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



std::shared_ptr<Shader> AssetManager::loadShader(std::string path, GLenum type){
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

