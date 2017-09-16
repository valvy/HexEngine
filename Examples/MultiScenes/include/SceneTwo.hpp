#ifndef SCENE_TWO_HPP
#define SCENE_TWO_HPP

#include <prutengine/AbstractScene.hpp>

class SceneTwo : public PrutEngine::AbstractScene{
public:
    SceneTwo();
    ~SceneTwo();
protected:
    virtual void awake() override;
    virtual void keyDown(const unsigned short& keycode) override;
    virtual void update(const float& tpf) override;
    

};

#endif
