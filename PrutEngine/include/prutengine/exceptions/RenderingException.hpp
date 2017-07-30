#ifndef PRUTENGINE_EXCEPTIONS_RENDERING_EXCEPTION_HPP
#define PRUTENGINE_EXCEPTIONS_RENDERING_EXCEPTION_HPP
#include "./PrutEngineException.hpp"
#include <vector>
namespace PrutEngine{
    namespace Exceptions{
        class RenderingException : public PrutEngineException{
            std::vector<std::string> errors;
            public:
            RenderingException(const std::string& msg);
            RenderingException(const char* msg);
            void addError(const std::string& error);

        };
    }
}

#endif