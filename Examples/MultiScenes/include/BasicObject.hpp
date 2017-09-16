#ifndef BASIC_OBJECT_HPP
#define BASIC_OBJECT_HPP

#include <prutengine/GameObject.hpp>

class BasicObject : public PrutEngine::GameObject{
protected:
    virtual void update(float tpf) override;
public:
    BasicObject(const PrutEngine::Math::Vector3f &position);
    ~BasicObject();
};


#endif