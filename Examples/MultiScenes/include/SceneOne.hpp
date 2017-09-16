#ifndef SCENE_ONE_HPP
#define SCENE_ONE_HPP

#include <prutengine/AbstractScene.hpp>

class SceneOne : public PrutEngine::AbstractScene{
public:
    SceneOne();
    ~SceneOne();
protected:
    virtual void awake() override;
    virtual void keyDown(unsigned short keycode) override;
    virtual void update(float tpf) override;
    

};

#endif
