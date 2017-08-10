#ifndef PRUTENGINE_GAMEOBJECT_HPP
#define PRUTENGINE_GAMEOBJECT_HPP
#include "./platform/OpenGL.hpp"
#include "./Application.hpp"
#include "./math/Quaternion.hpp"
#include "./Renderer.hpp"

namespace PrutEngine{
    class AbstractScene;

    class GameObject{
        friend AbstractScene;
    private:
        Math::Quaternion<float> quaternion;
        Math::Vector<float,3> scale;
        Math::Vector<float,3> position;
        std::shared_ptr<Renderer> renderer;
    protected:
        void setRenderer(std::shared_ptr<Renderer> renderer);
        virtual void update(float tpf);
        virtual void onKeyDown(unsigned short keycode);
        GameObject();
        public:
        std::shared_ptr<Renderer> getRenderer() const;
        void rotate(const Math::Vector<float,3>& vec, float angle);
        void translate(const Math::Vector<float,3>& vec, float speed);
        void setPosition(const Math::Vector<float,3> &position);
        void setScale(const Math::Vector<float,3> &scale);
        void setQuaternion(const Math::Quaternion<float> &quat);
        Math::Quaternion<float> getQuaternion() const;
        Math::Vector<float,3> getScale() const;
        Math::Vector<float,3> getPosition() const;
        virtual ~GameObject();
        
        

    };
}


#endif
