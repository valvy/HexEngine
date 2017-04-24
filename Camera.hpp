#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "GameObject.hpp"

class Camera : private GameObject{
    friend AbstractScene;
protected:
    virtual void update(float tpf);
    virtual void onScroll(float velocityX, float velocityY);
    virtual void onKeyDown(unsigned short keycode);
public:
    Camera(const Vector3<float>& startPos);
    
    void setPosition(const Vector3<float> &position);
    void rotate(const Vector3<float>& vec, float angle);
    void translate(const Vector3<float>& vec, float speed);
    
    Vector3<float> getPosition()const;
    
    void setQuaternion(const Quaternion<float>& quat);
    
    Quaternion<float> getQuaternion() const;

};



#endif