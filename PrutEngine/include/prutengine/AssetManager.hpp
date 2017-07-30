#ifndef PRUTENGINE_ASSET_MANAGER_HPP
#define PRUTENGINE_ASSET_MANAGER_HPP
#include <utility>
#include <string>
#include <vector>
#include "./platform/OpenGL.hpp"
#include "./data/Shader.hpp"
#include "./data/GLProgram.hpp"
#include "./data/Mesh.hpp"
#include "./data/Texture.hpp"

namespace PrutEngine{
    class AssetManager{
    private:
        static unsigned short uniqueNumber;
        
        static unsigned short getUniqueNumber();
        
        static std::vector<Data::Shader*> loadedShaders;
        static std::vector<Data::GLProgram*> loadedPrograms;
        static std::vector<Data::Mesh*> loadedMeshes;
        
        static std::vector<Data::Texture*> loadedTextures;
        
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
        
        static Data::Mesh* getMesh(unsigned short memoryPosition);
        static Data::Shader* getShader(unsigned short memoryPosition);
        
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
            
            Data::GLProgram* program = new Data::GLProgram(programName, getUniqueNumber(), usedShaders);
            loadedPrograms.push_back(program);
            
            
            return program->getMemoryPosition();
        }
    };
}




#endif
