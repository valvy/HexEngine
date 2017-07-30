#ifndef PRUTENGINE_TEST_OBJECT_HPP
#define PRUTENGINE_TEST_OBJECT_HPP
#include "../GameObject.hpp"



namespace PrutEngine{
    class TestObject : public GameObject{
    private:
        bool visible;
    protected:
        virtual void update(float tpf) override;
        virtual void onClick() override;
    public:
        [[deprecated("Should be moved to unit tests")]]
        TestObject(const Math::Vector3<float> &position);
    };
}

#endif