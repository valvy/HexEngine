#include "prutengine/exceptions/InitializationException.hpp"

using namespace PrutEngine::Exceptions;

InitializationException::InitializationException(const std::string& msg) : PrutEngineException(msg){
    
}

InitializationException::InitializationException(const char* msg) : PrutEngineException(msg){
    
}

void PrutEngine::Exceptions::assertNotInitialized(const bool assertation, const std::string& msg){
    if(assertation){
        throw InitializationException(msg);
    }
}