#include "prutengine/exceptions/NotYetInitializedException.hpp"

using namespace PrutEngine::Exceptions;

NotYetInitializedException::NotYetInitializedException(const std::string& msg) : PrutEngineException(msg){
    
}

NotYetInitializedException::NotYetInitializedException(const char* msg) : PrutEngineException(msg){
    
}