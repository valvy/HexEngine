#ifndef PRUTENGINE_GAMEOBJECT_HPP
#define PRUTENGINE_GAMEOBJECT_HPP

#include "./platform/OpenGL.hpp"
#include "./Application.hpp"
#include "./math/Quaternion.hpp"
#include "./Renderer.hpp"
#include "./Node.hpp"

//#include "./Transform.hpp"

namespace PrutEngine{
    class AbstractScene;

    class GameObject : public Node {
        friend AbstractScene;
    private:
        std::shared_ptr<Renderer> renderer;
    protected:
        void setRenderer(std::shared_ptr<Renderer> renderer);
        virtual void update(const float& tpf) override;
        GameObject();
        public:
        std::shared_ptr<Renderer> getRenderer() const;
        virtual ~GameObject();
        
        

    };
}


#endif
