#include "prutengine/exceptions/RenderingException.hpp"

using namespace PrutEngine::Exceptions;

RenderingException::RenderingException(const std::string& msg) : PrutEngineException(msg){

}

RenderingException::RenderingException(const char* msg) : PrutEngineException(msg){
    
}

void RenderingException::addError(const std::string& error){
    this->errors.push_back(error);
}