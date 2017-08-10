#include "prutengine/Transform.hpp"

using namespace PrutEngine;
using namespace PrutEngine::Math;
Transform::Transform(){
    
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
