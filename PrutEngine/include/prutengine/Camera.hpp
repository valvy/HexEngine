#ifndef PRUTENGINE_CAMERA_HPP
#define PRUTENGINE_CAMERA_HPP
#include "./GameObject.hpp"

namespace PrutEngine{
    class Camera : private GameObject{
        friend AbstractScene;
    protected:
        virtual void update(float tpf);
        virtual void onScroll(float velocityX, float velocityY);
        virtual void onKeyDown(unsigned short keycode);
    public:
        Camera(const Math::Vector3<float>& startPos);
        
        void setPosition(const Math::Vector3<float> &position);
        void rotate(const Math::Vector3<float>& vec, float angle);
        void translate(const Math::Vector3<float>& vec, float speed);
        
        Math::Vector3<float> getPosition()const;
        
        void setQuaternion(const Math::Quaternion<float>& quat);
        
        Math::Quaternion<float> getQuaternion() const;

    };

}




#endif