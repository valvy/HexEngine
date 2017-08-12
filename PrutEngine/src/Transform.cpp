#include "prutengine/Transform.hpp"

using namespace PrutEngine;
using namespace PrutEngine::Math;

Transform::Transform(){
    
}

Transform::Transform(const Math::Vector3f& position, const Math::Vector3f& scale, const Math::Quaternion<float>& quaternion){
    this->position = position;
    this->scale = scale;
    this->quaternion = quaternion;
}

void Transform::rotate(const Math::Vector3f& vec, float angle){
    this->quaternion = Quaternion<float>::rotate(quaternion, vec,angle);
}

void Transform::translate(const Math::Vector3f& vec, float speed){
    this->position.setX(this->position.getX() + vec.getX() * speed);
    this->position.setY(this->position.getY() + vec.getY() * speed);
    this->position.setZ(this->position.getZ() + vec.getZ() * speed);
}

void Transform::setPosition(const Math::Vector3f &position){
    this->position = position;
}

void Transform::setScale(const Math::Vector3f &scale){
    this->scale = scale;
}

void Transform::setQuaternion(const Math::Quaternion<float> &quat){
    this->quaternion = quat;
}

Math::Quaternion<float> Transform::getQuaternion() const{
    return this->quaternion;
}


Math::Vector3f Transform::getScale() const{
    return this->scale;
}

Math::Vector3f Transform::getPosition() const{
    return this->position;
}

