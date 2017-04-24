#ifndef HEX_HPP
#define HEX_HPP
#include "GameObject.hpp"

class Hex : public GameObject{
private:
    bool visible;
protected:
    virtual void update(float tpf) override;
    virtual void onClick() override;
public:
    Hex(const Vector3<float> &position);
};


#endif