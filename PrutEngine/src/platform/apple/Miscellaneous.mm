#import "prutengine/AssetManager.hpp"
#import <Cocoa/Cocoa.h>
using namespace PrutEngine;

std::string AssetManager::getAppPath() const{
    return [[[NSBundle mainBundle]resourcePath]UTF8String];
}