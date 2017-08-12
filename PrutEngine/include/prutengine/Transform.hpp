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
        Transform(const Math::Vector3f& position, const Math::Vector3f& scale, const Math::Quaternion<float>& quaternion);
        Math::Quaternion<float> getQuaternion() const;
        Math::Vector3f getScale() const;
        Math::Vector3f getPosition() const;
        void rotate(const Math::Vector3f& vec, float angle);
        void translate(const Math::Vector3f& vec, float speed);
        void setPosition(const Math::Vector3f& position);
        void setScale(const Math::Vector3f& scale);
        void setQuaternion(const Math::Quaternion<float> &quat);
    };
}

#endif
