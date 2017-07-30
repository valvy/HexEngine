#ifndef PRUTENGINE_EXCEPTIONS_PRUTENGINE_EXCEPTION_HPP
#define PRUTENGINE_EXCEPTIONS_PRUTENGINE_EXCEPTION_HPP
#include <string>
namespace PrutEngine{
    namespace Exceptions{
        class PrutEngineException{
            std::string msg;
            public:
            PrutEngineException(std::string msg){
                this->msg = msg;
            }
            PrutEngineException(const char* msg){
                this->msg = std::string(msg);
            }
            std::string getMsg() const {
                return this->msg;
            }
        };
    }
}

#endif