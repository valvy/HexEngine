#ifndef BASIC_SCENE_HPP
#define BASIC_SCENE_HPP
#include <prutengine/AbstractScene.hpp>




class BasicScene : public PrutEngine::AbstractScene{
public:
    BasicScene();
protected:
    virtual void awake() override;
    virtual void keyDown(unsigned short keycode) override;
    virtual void update(float tpf) override;


};



#endif
