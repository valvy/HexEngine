#ifndef MESH_HPP
#define MESH_HPP
#include "AbstractResource.hpp"
#include "OpenGL.hpp"
#include <vector>
class Mesh : public AbstractResource{
private:
    GLuint vao;
    GLuint vboVertex;
    GLuint vboUV;
    GLuint vboNormal;
    int size;
    GLuint storeDataInVao(int attributeNr, int size, const std::vector<GLfloat> &data);
public:
    Mesh(std::string path, unsigned short uniqueNumber);
    ~Mesh();
    int getSize() const;
    GLuint getVao() const;
};



#endif