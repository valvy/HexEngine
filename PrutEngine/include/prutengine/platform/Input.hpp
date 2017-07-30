#ifndef PRUTENGINE_INPUT_HPP
#define PRUTENGINE_INPUT_HPP

namespace PrutEngine{
    /*! All the different keycodes for the different operating systems
    *  @author Heiko van der Heijden
    */
    namespace KeyCodes {
        constexpr unsigned short LEFT_MOUSE = 5000;
    #ifdef __APPLE__

        constexpr unsigned short SPACE_BAR = 49;
        constexpr unsigned short UP_KEY = 126;
        constexpr unsigned short DOWN_KEY = 125;
        constexpr unsigned short LEFT_KEY = 124;
        constexpr unsigned short RIGHT_KEY = 123;
        constexpr unsigned short ESCAPE_KEY = 53;

    #endif
    #ifdef __linux__
        constexpr unsigned short SPACE_BAR = 65;
        constexpr unsigned short UP_KEY = 111;
        constexpr unsigned short DOWN_KEY = 116;
        constexpr unsigned short LEFT_KEY = 114;
        constexpr unsigned short RIGHT_KEY = 113;
        constexpr unsigned short ESCAPE_KEY = 9;

    #endif

    }

    class Input{
        
    };
}

#endif

