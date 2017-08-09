#ifndef PRUTENGINE_CAMERA_HPP
#define PRUTENGINE_CAMERA_HPP
#include "./GameObject.hpp"

namespace PrutEngine{
    class Camera : private GameObject{
        friend AbstractScene;
    protected:
        virtual void update(float tpf);
        virtual void onKeyDown(unsigned short keycode);
    public:
        Camera(const Math::Vector<float,3>& startPos);
        
        void setPosition(const Math::Vector<float,3> &position);
        void rotate(const Math::Vector<float,3>& vec, float angle);
        void translate(const Math::Vector<float,3>& vec, float speed);
        
        Math::Vector<float,3> getPosition()const;
        
        void setQuaternion(const Math::Quaternion<float>& quat);
        
        Math::Quaternion<float> getQuaternion() const;

    };

}




#endif
