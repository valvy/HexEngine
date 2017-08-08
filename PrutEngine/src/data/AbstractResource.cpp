#include "prutengine/data/AbstractResource.hpp"

using namespace PrutEngine;
using namespace PrutEngine::Data;

AbstractResource::AbstractResource(const std::string& path) : dataLocation(path){
    
}

AbstractResource::~AbstractResource(){
}

std::string AbstractResource::getDataLocation() const{
	return this->dataLocation;
}







