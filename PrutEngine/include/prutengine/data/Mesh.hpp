#ifndef PRUTENGINE_MESH_HPP
#define PRUTENGINE_MESH_HPP
#include "AbstractResource.hpp"
#include "../platform/OpenGL.hpp"
#include <vector>
namespace PrutEngine{
    namespace Data{
        class Mesh : public AbstractResource{
        private:
            GLuint vao;
            GLuint vboVertex;
            GLuint vboUV;
            GLuint vboNormal;
            int size;
            GLuint storeDataInVao(int attributeNr, int size, const std::vector<GLfloat> &data);
        public:
            Mesh(std::string path);
            ~Mesh();
            int getSize() const;
            GLuint getVao() const;
        };
    }
}


#endif