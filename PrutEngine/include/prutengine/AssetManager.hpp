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
        
        std::vector<std::shared_ptr<Data::Shader> > loadedShaders;
        std::vector<std::shared_ptr<Data::GLProgram> > loadedPrograms;
        std::vector<std::shared_ptr<Data::Mesh> > loadedMeshes;
        
        std::vector<std::shared_ptr<Data::Texture> > loadedTextures;
        
        std::shared_ptr<Data::Shader> loadShader(const std::string& path, Shader_Types type);
        
        std::vector<std::shared_ptr<Data::Shader>> massLoadShader(std::pair<std::string,Shader_Types> head){
            std::vector<std::shared_ptr<Data::Shader>> result;
            result.push_back(loadShader(head.first,head.second));
            return result;
        }
        
        template<typename... Arguments>
        std::vector<std::shared_ptr<Data::Shader>> massLoadShader(std::pair<std::string, Shader_Types> head, Arguments... tail){
            std::vector<std::shared_ptr<Data::Shader>> result = AssetManager::loadShader(tail...);
            result.push_back(loadShader(head.first,head.second));
            return result;
            
        }
    public:
        void clear();
        
        std::shared_ptr<Data::Mesh> loadMesh(const std::string& path);
        
        std::string getAppPath() const;

        std::vector<GLuint> allPrograms();
        
        
        std::shared_ptr<Data::Texture> loadTexture(const std::string& path);
        
        template<typename... Arguments>
        std::shared_ptr<Data::GLProgram> loadProgram(std::pair<std::string, Shader_Types> head, Arguments... shaders){
            
            auto usedShaders = this->massLoadShader(shaders...);
            usedShaders.push_back(loadShader(head.first,head.second));
            std::string programName;
            
            for(auto it : usedShaders){
                programName += it->getDataLocation();
            }
            //Check if the program is loaded
            for(auto it : loadedPrograms){
                if(it->getDataLocation() == programName){
                    return it;
                }
            }
            
            auto program = std::shared_ptr<Data::GLProgram>(new Data::GLProgram(programName, usedShaders));
            loadedPrograms.push_back(program);
            
            return program;
            //return program->getMemoryPosition();
        }
    };
}




#endif
