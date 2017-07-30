#ifndef ABSTRACT_RESOURCE_HPP
#define ABSTRACT_RESOURCE_HPP
#include <string>

class AbstractResource{
private:
	unsigned short memoryPosition;
	std::string dataLocation;
	unsigned short amountOfRef;
public:
    AbstractResource(std::string path, unsigned short uniqueNumber);
	std::string getDataLocation() const;
	bool removeRef();
	unsigned short addRef();
	unsigned short getMemoryPosition() const;
protected: 
	

};

#endif
