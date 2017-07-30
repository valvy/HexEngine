#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP
#include <utility>
#include <string>
#include "OpenGL.hpp"
#include <vector>
#include "Shader.hpp"
#include "GLProgram.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"

class AssetManager{
private:
    static unsigned short uniqueNumber;
    
    static unsigned short getUniqueNumber();
    
    static std::vector<Shader*> loadedShaders;
    static std::vector<GLProgram*> loadedPrograms;
    static std::vector<Mesh*> loadedMeshes;
    
    static std::vector<Texture*> loadedTextures;
    
    static unsigned short loadShader(std::string path, GLenum type);
    
    static std::vector<unsigned short> massLoadShader(std::pair<std::string,GLenum> head){
        std::vector<unsigned short> result;
        result.push_back(loadShader(head.first,head.second));
        return result;
    }
    
    template<typename... Arguments>
    static std::vector<unsigned short> massLoadShader(std::pair<std::string, GLenum> head, Arguments... tail){
        std::vector<unsigned short> result = AssetManager::loadShader(tail...);
        result.push_back(loadShader(head.first,head.second));
        return result;
        
    }
public:
    static void clear();
    
    static unsigned short loadMesh(std::string path);
    
    static GLuint getProgram(unsigned short memoryPosition);
    
    static Mesh* getMesh(unsigned short memoryPosition);
    static Shader* getShader(unsigned short memoryPosition);
    
    static std::vector<GLuint> allPrograms();
    
    
    static unsigned short loadTexture(std::string path);
    static GLuint getTexture(unsigned short memoryPosition);
    
    
    
    template<typename... Arguments>
    static unsigned short loadProgram(std::pair<std::string, GLenum> head, Arguments... shaders){
       
        std::vector<unsigned short> usedShaders = AssetManager::massLoadShader(shaders...);
        usedShaders.push_back(loadShader(head.first,head.second));
        std::string programName;
        
        for(auto it : usedShaders){
            programName += getShader(it)->getDataLocation();
        }
        //Check if the program is loaded
        for(auto it : loadedPrograms){
            if(it->getDataLocation() == programName){
                return it->getMemoryPosition();
            }
        }
        
        GLProgram* program = new GLProgram(programName, getUniqueNumber(), usedShaders);
        loadedPrograms.push_back(program);
        
        
        return program->getMemoryPosition();
    }
};


#endif
