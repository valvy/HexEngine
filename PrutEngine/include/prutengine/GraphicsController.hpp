#ifndef PRUTENGINE_GRAPHICS_CONTROLLER_HPP
#define PRUTENGINE_GRAPHICS_CONTROLLER_HPP
#include <functional>
namespace PrutEngine{

    class Application;

    class GraphicsController{
        friend Application;        
        std::function<void()> function;
    };
}

#endif