#include "BasicApplication.hpp"
#include "BasicScene.hpp"
#include <iostream>

BasicApplication::BasicApplication(){
    setInstance(this);
    loadScene(std::shared_ptr<PrutEngine::AbstractScene>(new BasicScene()));
    run();

}


void BasicApplication::loop(){
    update();
}

BasicApplication::~BasicApplication(){
    std::cout << "Quitting\n";
}