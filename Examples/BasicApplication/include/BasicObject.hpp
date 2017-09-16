#ifndef BASIC_OBJECT_HPP
#define BASIC_OBJECT_HPP

#include <prutengine/GameObject.hpp>

class BasicObject : public PrutEngine::GameObject{
private:
    bool visible;
protected:
    virtual void update(const float& tpf) override;
public:
    BasicObject(const PrutEngine::Math::Vector3f &position);
};


#endif