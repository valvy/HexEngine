#include "prutengine/data/AbstractResource.hpp"

using namespace PrutEngine;

AbstractResource::AbstractResource(std::string path, unsigned short uniqueNumber) : memoryPosition(uniqueNumber), dataLocation(path){
    
}

std::string AbstractResource::getDataLocation() const{
	return this->dataLocation;
}

bool AbstractResource::removeRef(){
	this->amountOfRef--;
	return amountOfRef == 0;
}



unsigned short AbstractResource::addRef(){
	this->amountOfRef++;
	return this->memoryPosition;
}

unsigned short AbstractResource::getMemoryPosition() const{
	return this->memoryPosition;
}



