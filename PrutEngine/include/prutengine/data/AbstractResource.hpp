#ifndef PRUTENGINE_ABSTRACT_RESOURCE_HPP
#define PRUTENGINE_ABSTRACT_RESOURCE_HPP
#include <string>
namespace PrutEngine{
	namespace Data{
		class AbstractResource{
		private:
			std::string dataLocation;
		public:
			AbstractResource(const std::string& path);
			~AbstractResource();
			std::string getDataLocation() const;
		protected: 
			

		};
	}
}


#endif
