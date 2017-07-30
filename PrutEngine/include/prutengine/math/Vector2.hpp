#ifndef PRUTENGINE_MATH_VECTOR_2_HPP
#define PRUTENGINE_MATH_VECTOR_2_HPP

namespace PrutEngine{
    namespace Math{
        template<typename T>
        struct Vector2{
            T x;
            T y;
            
            Vector2(T x, T y) : x(x) , y(y){}
            
            Vector2(){
                x = 0;
                y = 0;
            }
        };
    }
}



#endif