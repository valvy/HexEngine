#ifndef PRUTENGINE_PRUT_WINDOW_HPP
#define PRUTENGINE_PRUT_WINDOW_HPP

#include<string>
#include "prutengine/math/Vector.hpp"

namespace PrutEngine{

    class Application;

    class PrutWindow{
        friend Application;
    private:
        PrutWindow();
    public:
        Math::Vector4f getWindowSize() const;
        void setWindowTitle(const std::string& title);
    };
}

#endif