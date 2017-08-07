#ifndef PRUTENGINE_EXCEPTIONS_NOT_YET_INITIALIZED_EXCEPTION_HPP
#define PRUTENGINE_EXCEPTIONS_NOT_YET_INITIALIZED_EXCEPTION_HPP
#include "./PrutEngineException.hpp"
namespace PrutEngine{
    namespace Exceptions{
        class NotYetInitializedException : public PrutEngineException{
            public:
            NotYetInitializedException(const std::string& msg);
            NotYetInitializedException(const char* msg);
        };

        void assertNotYetInitialized(const bool assertation, const std::string& msg);
    }
}
#endif