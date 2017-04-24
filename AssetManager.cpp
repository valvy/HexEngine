#include "AssetManager.hpp"
#include <iostream>
unsigned short AssetManager::uniqueNumber = 0;

std::vector<Shader*> AssetManager::loadedShaders;

std::vector<GLProgram*> AssetManager::loadedPrograms;
std::vector<Mesh*> AssetManager::loadedMeshes;
std::vector<Texture*> AssetManager::loadedTextures;


std::vector<GLuint> AssetManager::allPrograms(){
    std::vector<GLuint> result;
    for(auto it : AssetManager::loadedPrograms){
        result.push_back(it->getProgram());
    }
    return result;
}

GLuint AssetManager::getTexture(unsigned short memoryPosition){
    for(auto it : AssetManager::loadedTextures){
        if(it->getMemoryPosition() == memoryPosition){
            return it->getTexture();
        }
    }
    return 0;
}

unsigned short AssetManager::loadTexture(std::string path){
    for(auto it : AssetManager::loadedTextures){
        if(it->getDataLocation() == path){
            it->addRef();
            return it->getMemoryPosition();
        }
    }
    
    Texture* t = new Texture(path, getUniqueNumber());
    loadedTextures.push_back(t);
    return t->getMemoryPosition();
}

unsigned short AssetManager::loadMesh(std::string path){
    for(auto it : AssetManager::loadedPrograms){
        if(it->getDataLocation() == path){
            it->addRef();
            return it->getMemoryPosition();
        }
    }
    
    Mesh* m = new Mesh(path,getUniqueNumber());
    loadedMeshes.push_back(m);
    return m->getMemoryPosition();
    
}

void AssetManager::clear(){
    for(auto it : loadedShaders){
        delete it;
    }
    
    for(auto it : loadedPrograms){
        delete it;
    }
    
    for(auto it : loadedMeshes){
        delete it;
    }
    for(auto it : loadedTextures){
        delete it;
    }
    loadedTextures.clear();
    loadedShaders.clear();
    loadedPrograms.clear();
    loadedMeshes.clear();
}

GLuint AssetManager::getProgram(unsigned short memoryPosition){
    for(auto it : loadedPrograms){
        if(it->getMemoryPosition() == memoryPosition){
            return it->getProgram();
        }
    }
    throw std::string("Could not find the resource\n");
}

Mesh* AssetManager::getMesh(unsigned short memoryPosition){
    for(auto it : loadedMeshes){
        if(it->getMemoryPosition() == memoryPosition){
            return it;
        }
    }
    throw std::string("Could not find the resource\n");
}

Shader* AssetManager::getShader(unsigned short memoryPosition){
    for(auto it : loadedShaders){
        if(it->getMemoryPosition() == memoryPosition){
            return it;
        }
    }
    throw std::string("could not find the resource\n");
}


unsigned short AssetManager::loadShader(std::string path, GLenum type){
    //Check if the shader already exists
    for(auto it : AssetManager::loadedShaders){
        if(it->getDataLocation() == path){
            it->addRef();
            return it->getMemoryPosition();
        }
    }
    
    Shader* sh = new Shader(path,type,getUniqueNumber());
    loadedShaders.push_back(sh);
    return sh->getMemoryPosition();
    
}

unsigned short AssetManager::getUniqueNumber(){
    unsigned short res = AssetManager::uniqueNumber;
    AssetManager::uniqueNumber++;
    return res;
}

/*unsigned short AssetManager::loadProgram(std::initializer_list<std::pair<std::string,GLenum>> dat){
    
    return 0;
}*/