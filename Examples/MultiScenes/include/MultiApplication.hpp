#ifndef MULTI_SCENE_APPLICATION_HPP
#define MULTI_SCENE_APPLICATION_HPP

#include <prutengine/Application.hpp>

class MultiSceneApplication : public PrutEngine::Application{
    public:
    MultiSceneApplication();
    virtual void loop() override;
    virtual PrutEngine::Graphics_Engine setRenderer() override;
    ~MultiSceneApplication();
};

#endif