#include "prutengine/GraphicsController.hpp"
#include "prutengine/exceptions/AssetNotLoadedException.hpp"
using namespace PrutEngine;

void GraphicsController::draw(){
    try{
    this->drawGraphics();
    } catch(const std::bad_function_call exception){
        throw Exceptions::AssetNotLoadedException("Draw function was not setup");
    }
}
