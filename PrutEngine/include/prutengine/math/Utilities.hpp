#ifndef PRUTENGINE_MATH_UTILITIES_HPP
#define PRUTENGINE_MATH_UTILITIES_HPP

namespace PrutEngine{
    namespace Math {
        template<typename T>
        struct Matrix4x4;
        constexpr float PI = 3.1415926f;

        
        template<typename T>
        Matrix4x4<T> frustum(T right, T left, T top, T bottom, T near, T far){
    
            if((right == left) ||
            (top == bottom) ||
            (near == far) ||
            (near < 0.0) ||
            (far < 0.0)){
                return Matrix4x4<T>();
            }
            
            Vector<T,4> r1((2 * near) / (right * left),0.0,(right + left) / (right - left), 0);
            
            Vector<T,4> r2(0, (2 * near) / (top - bottom), (top + bottom) / (top - bottom), 0.0);
            Vector<T,4> r3(0,0, (near + far) / (near - far), -(2 * near * far) / (near - far));
            Vector<T,4> r4(0,0,-1.0,0);
            
            
            return Matrix4x4<T>(r1, r2,r3,r4);
        }
        
        template<typename T>
        Matrix4x4<T> perspective(T fovy, T aspect, T near, T far){
            
            T q = 1.0f / tan((0.5f * fovy) * (PI / 180));        //1 / tan(radians(0.5f * fovy));
            T A = q / aspect;
            T B = (near + far) / (near - far);
            T C = (2.0f * near * far) / (near - far);
            
            return Matrix4x4<T>(
                Vector<T,4>(A,0,0,0),
                Vector<T,4>(0,q,0,0),
                Vector<T,4>(0,0,B,-1),
                Vector<T,4>(0,0,C,0));
        }
        
        template<typename T>
        Matrix4x4<T> orthographic(T left, T right, T bottom, T top, T near, T far){

            
            
            return Matrix4x4<T>(
                                Vector<T, 4>(2.0f / (right - left), 0.0f, 0.0f,0.0f),
                                Vector<T, 4>(0.0f, 2.0f / (top - bottom) ,0.0f, 0.0f),
                                Vector<T, 4>(0.0f,0.0f, 2.0f / (near - far),0.0f),
                                Vector<T, 4>((left + right) / (left - right), (bottom + top) / (bottom - top), (near + far) / (far - near), 1.0f));
            
        }

    }
}

#endif
