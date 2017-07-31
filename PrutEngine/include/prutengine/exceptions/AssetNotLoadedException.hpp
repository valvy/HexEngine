#ifndef PRUTENGINE_EXCEPTIONS_ASSET_NOT_LOADED_EXCEPTION_HPP
#define PRUTENGINE_EXCEPTIONS_ASSET_NOT_LOADED_EXCEPTION_HPP
#include "./PrutEngineException.hpp"
namespace PrutEngine{
    namespace Exceptions{
        class AssetNotLoadedException : public PrutEngineException{
            public:
            AssetNotLoadedException(const std::string& msg);
            AssetNotLoadedException(const char* msg);
        };
    }
}
#endif