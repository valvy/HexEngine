#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
#import <string>

#import "prutengine/platform/IOSApp.h"
#import "prutengine/AssetManager.hpp"
#import "prutengine/exceptions/PrutEngineException.hpp"
#import "prutengine/platform/Input.hpp"

using namespace PrutEngine;

using namespace PrutEngine::Math;

Vector4<float> Application::getWindowSize() const{
    //NSSize s = [app frame].size;
    //NSPoint p = [app frame].origin;
    return Vector4<float>(0, 0, 100,100);
}

void Application::quit(){
    auto assetManager =  Application::getInstance()->getAssetManager();
    assetManager->clear();
    currentScene.reset();
    //delete Application::instance;
    
}

std::string Application::getAppPath() const{
   return "";
}

void Application::run(){
    
}


#endif
#endif
