#ifndef PRUTENGINE_GRAPHICS_CONTROLLER_HPP
#define PRUTENGINE_GRAPHICS_CONTROLLER_HPP
#include <functional>
namespace PrutEngine{

    //class Application;

    #ifdef __APPLE__
	namespace Platform{class MacRenderer; };
	#endif

    class GraphicsController{
        //friend Application;        
        #ifdef __APPLE__
        friend Platform::MacRenderer;
        #endif
        
        private:
        std::function<void()> drawGraphics;
        
        public:
        void draw();

    };
}

#endif