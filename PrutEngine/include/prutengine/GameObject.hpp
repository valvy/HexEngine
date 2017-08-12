#ifndef PRUTENGINE_GAMEOBJECT_HPP
#define PRUTENGINE_GAMEOBJECT_HPP
#include "./platform/OpenGL.hpp"
#include "./Application.hpp"
#include "./math/Quaternion.hpp"
#include "./Renderer.hpp"
#include "./Transform.hpp"

namespace PrutEngine{
    class AbstractScene;

    class GameObject{
        friend AbstractScene;
    private:
        std::shared_ptr<Transform> transform;
        std::shared_ptr<Renderer> renderer;
    protected:
        void setRenderer(std::shared_ptr<Renderer> renderer);
        virtual void update(float tpf);
        virtual void onKeyDown(unsigned short keycode);
        GameObject();
        public:
        std::shared_ptr<Transform> getTransform() const;
        std::shared_ptr<Renderer> getRenderer() const;
        virtual ~GameObject();
        
        

    };
}


#endif
