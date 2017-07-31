#ifndef BASIC_APPLICATION_HPP
#define BASIC_APPLICATION_HPP
#include <prutengine/Application.hpp>

class BasicApplication : public PrutEngine::Application{
    public:
    BasicApplication();
    virtual void loop() override;
};

#endif