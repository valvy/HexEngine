#ifndef PRUTENGINE_EXCEPTIONS_INITIALIZED_EXCEPTION_HPP
#define PRUTENGINE_EXCEPTIONS_INITIALIZED_EXCEPTION_HPP
#include "./PrutEngineException.hpp"
namespace PrutEngine{
    namespace Exceptions{
        class InitializationException : public PrutEngineException{
            public:
            InitializationException(const std::string& msg);
            InitializationException(const char* msg);
        };

        void assertNotInitialized(const bool assertation, const std::string& msg);
    }
}
#endif