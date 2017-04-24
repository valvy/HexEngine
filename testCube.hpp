#ifndef TEST_CUBE_HPP
#define TEST_CUBE_HPP
#include "GameObject.hpp"

class TestCube : public GameObject{
protected:
    virtual void update(float tpf) override;
public:
    TestCube(const Vector3<float> &position);
};


#endif