#ifndef PRUTENGINE_RENDERER_HPP
#define PRUTENGINE_RENDERER_HPP
#include "./data/Mesh.hpp"
#include "./data/GraphicsProgram.hpp"
#include "./data/Texture.hpp"
#include "./Application.hpp"
#include <memory>


namespace PrutEngine {
    class Renderer{
        private:
        std::shared_ptr<Data::Mesh> mesh;
        std::shared_ptr<Data::GraphicsProgram> program;
        std::shared_ptr<Data::Texture> texture;
        protected:
        void set(const std::string& mesh, const std::string& texture, std::shared_ptr<Data::GraphicsProgram> program);
        public:
        std::shared_ptr<Data::Mesh> getMesh() const;
        std::shared_ptr<Data::GraphicsProgram> getProgram() const;
        std::shared_ptr<Data::Texture> getTexture() const;
        public:
        ~Renderer();
    };
    
    class GLRenderer : public Renderer{
        GLint pos_reference;
        public:
        GLRenderer(const std::string& mesh, const std::string& texture, std::shared_ptr<Data::GraphicsProgram> program);
        virtual ~GLRenderer();
        GLint getPositionRef() const;
        private:
    
    };
}

#endif
