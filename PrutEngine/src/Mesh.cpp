#include "prutengine/data/Mesh.hpp"
#include <fstream>
#include <regex>
#include "prutengine/math/Vector.hpp"
#include "prutengine/exceptions/AssetNotLoadedException.hpp"
using namespace PrutEngine;
using namespace PrutEngine::Data;

Mesh::Mesh(std::string path) : AbstractResource(path){
    using namespace PrutEngine::Math;
    glGenVertexArrays(1,&this->vao);
    glBindVertexArray(this->vao);
    
    std::fstream str(path, std::ios::in);
    if(str.good()){
        std::string line;
        std::vector<std::string> data;
        
        while(!str.eof()){
            std::getline(str,line);
            data.push_back(line);
        }
        str.close();
        
        std::vector<Vector3<float>> vertex;
        std::vector<Vector2<float>> texture;
        std::vector<Vector3<float>> normals;
        std::vector<Vector3<Vector3<int>>> verticesList;
        //Put the data in arrays
        for(std::string dat : data){
            if(dat.substr(0,1) == "#"){
                continue;
            }
            const std::regex tokenThree ("\\s*([a-z|A-Z]+)\\s*(-?[0-9]+.[0-9]+)\\s*(-?[0-9]+.[0-9]+)\\s*(-?[0-9]+.[0-9]+)\\s*",std::regex::ECMAScript);
            const std::regex tokenTwo ("\\s*([a-z|A-Z]+)\\s*(-?[0-9]+.[0-9]+)\\s*(-?[0-9]+.[0-9]+)\\s*",std::regex::ECMAScript);
            std::smatch match;
            std::regex_match(dat, match, tokenThree);
            if(match[1] == "v"){
                vertex.push_back(Vector3<float>(
                    std::stof(match[2]),
                    std::stof(match[3]),
                    std::stof(match[4])
                    ));
            }
            else if(match[1] == "vn"){
                normals.push_back(Vector3<float>(
                    std::stof(match[2]),
                    std::stof(match[3]),
                    std::stof(match[4])
                    ));
            }
            if(dat.substr(0,2) == "vt"){
                float x, y;
                sscanf(dat.c_str(), "vt %f %f", &x, &y);
                texture.push_back(Vector2<float>(x,y));
            }
            else if(dat.substr(0,2) == "f "){
                Vector3<Vector3<int>> vertices;
                int a,b,c,d,e,f,g,h, i;
                const int matches = sscanf(dat.c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d",
                   &a,&b,&c,&d,&e,&f,&g,&h, &i
                   /*    &vertices.getX().getX(),
                       &vertices.getX().getY(),
                       &vertices.getX().getZ(),
                       &vertices.getY().getX(),
                       &vertices.getY().getY(),
                       &vertices.getY().getZ(),
                       &vertices.getZ().getX(),
                       &vertices.getZ().getY(),
                       &vertices.getZ().getZ()
                    */
                       );
                vertices.setX(Vector3<int>(a,b,c));
                vertices.setY(Vector3<int>(d,e,f));
                vertices.setZ(Vector3<int>(g,h,i));

                
                if(matches != 9){
                   //  LOG(WARNING)  <<"error\n";
                   throw Exceptions::AssetNotLoadedException("Invalid input detected!");
                }
                verticesList.push_back(vertices);
            }
        }
        
        std::vector<GLfloat> rawVertexData;
        std::vector<GLfloat> rawUVData;
        std::vector<GLfloat> rawNormalData;
        
        //setup vbo's
        for(auto vertices : verticesList){
            Vector3<float> v = vertex[vertices.getX().getX() - 1];
         
            Vector2<float> uv = texture[vertices.getX().getY() -1];
            Vector3<float> norm = normals[vertices.getX().getZ() -1];
            rawVertexData.push_back(v.getX());
            rawVertexData.push_back(v.getY());
            rawVertexData.push_back(v.getZ());
            
            rawUVData.push_back(uv.getX());
            rawUVData.push_back(uv.getY());

            rawNormalData.push_back(norm.getX());
            rawNormalData.push_back(norm.getY());
            rawNormalData.push_back(norm.getZ());
            
            
            v = vertex[vertices.getY().getX() - 1];
            uv = texture[vertices.getY().getY() -1];
            norm = normals[vertices.getY().getZ() -1];
            rawVertexData.push_back(v.getX());
            rawVertexData.push_back(v.getY());
            rawVertexData.push_back(v.getZ());
            
            rawUVData.push_back(uv.getX());
            rawUVData.push_back(uv.getY());
            
            rawNormalData.push_back(norm.getX());
            rawNormalData.push_back(norm.getY());
            rawNormalData.push_back(norm.getZ());
            
            v = vertex[vertices.getZ().getX() - 1];
            uv = texture[vertices.getZ().getY() -1];
            norm = normals[vertices.getZ().getZ() -1];
            rawVertexData.push_back(v.getX());
            rawVertexData.push_back(v.getY());
            rawVertexData.push_back(v.getZ());
            
            rawUVData.push_back(uv.getX());
            rawUVData.push_back(uv.getY());
            
            rawNormalData.push_back(norm.getX());
            rawNormalData.push_back(norm.getY());
            rawNormalData.push_back(norm.getZ());
        }
        
        this->vboVertex = this->storeDataInVao(0,3, rawVertexData);
        this->vboUV = this->storeDataInVao(1,2, rawUVData);
        this->vboNormal = this->storeDataInVao(2, 3, rawNormalData);
        this->size = verticesList.size() * 3;
    }
    else{
        throw Exceptions::AssetNotLoadedException("Could not find the file!");
    }
    
  
    
}

GLuint Mesh::storeDataInVao(int attributeNr, int size,const std::vector<GLfloat> &data){
    GLuint vboId;
    glGenBuffers(1, &vboId);
    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glEnableVertexAttribArray(attributeNr);
    glBufferData(GL_ARRAY_BUFFER, data.size() * 3 * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNr, size, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindVertexArray(0);
    return vboId;
}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1,&this->vboVertex);
    glDeleteBuffers(1,&this->vboUV);
    glDeleteBuffers(1,&this->vboNormal);
}

int Mesh::getSize() const{
    return this->size;
}

GLuint Mesh::getVao() const{
    return this->vao;
}