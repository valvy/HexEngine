#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include "AbstractResource.hpp"
#include "OpenGL.hpp"

class Texture : public AbstractResource{
private:
    GLuint texture;
public:
    Texture(std::string name, unsigned short uniqueNumber);
    ~Texture();
    GLuint getTexture() const;
};



#endif