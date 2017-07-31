#include "BasicApplication.hpp"
#include "BasicScene.hpp"
#include <iostream>

BasicApplication::BasicApplication(){
    setInstance(this);
    loadScene(std::shared_ptr<PrutEngine::AbstractScene>(new BasicScene()));
    initialize();

}


void BasicApplication::loop(){
    update();
}