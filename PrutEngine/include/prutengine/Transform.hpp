#ifndef PRUTENGINE_TRANSFORM_HPP
#define PRUTENGINE_TRANSFORM_HPP
#include "./math/Quaternion.hpp"


namespace PrutEngine{
    class Transform{
        Math::Quaternion<float> quaternion;
        Math::Vector3f scale;
        Math::Vector3f position;
        public:
        Transform();
        Math::Quaternion<float> getQuaternion() const;
        Math::Vector3f getScale() const;
        Math::Vector3f getPosition() const;
        
    };
}

#endif
