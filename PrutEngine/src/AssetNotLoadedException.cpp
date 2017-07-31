#include "prutengine/exceptions/AssetNotLoadedException.hpp"

using namespace PrutEngine::Exceptions;

AssetNotLoadedException::AssetNotLoadedException(const std::string& msg) : PrutEngineException(msg){
    
}

AssetNotLoadedException::AssetNotLoadedException(const char* msg) : PrutEngineException(msg){
    
}