#include "prutengine/exceptions/NotYetInitializedException.hpp"

using namespace PrutEngine::Exceptions;

NotYetInitializedException::NotYetInitializedException(const std::string& msg) : PrutEngineException(msg){
    
}

NotYetInitializedException::NotYetInitializedException(const char* msg) : PrutEngineException(msg){
    
}

void PrutEngine::Exceptions::assertNotYetInitialized(const bool assertation, const std::string& msg){
    if(assertation){
        throw NotYetInitializedException(msg);
    }
}