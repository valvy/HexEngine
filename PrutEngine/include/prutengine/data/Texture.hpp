#ifndef PRUTENGINE_TEXTURE_HPP
#define PRUTENGINE_TEXTURE_HPP
#include "./AbstractResource.hpp"
#include "../platform/OpenGL.hpp"
namespace PrutEngine{
    namespace Data{
        class Texture : public AbstractResource{
        private:
            GLuint texture;
        public:
            Texture(std::string name, unsigned short uniqueNumber);
            ~Texture();
            GLuint getTexture() const;
        };
    }
}


#endif