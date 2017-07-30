#ifndef PRUTENGINE_MATH_VECTOR4_HPP
#define PRUTENGINE_MATH_VECTOR4_HPP
#include <iostream>

namespace PrutEngine{
    namespace Math{
        template<typename T>
        struct Vector4{
            T x, y, z, w;
            Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w){}
            Vector4(){}
            
            Vector4<T>& operator=(Vector4<T> other){
                this->x = other.x;
                this->y = other.y;
                this->z = other.z;
                this->w = other.w;
                return *this;
            }
            
            T inProduct(Vector4<T> other){
                return (this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w);
            }
            
            Vector4<T>& operator-(Vector4<T> other){
                this->x += -1 * other.x;
                this->y += -1 * other.y;
                this->z += -1 * other.z;
                this->w += -1 * other.w;
                return *this;
            }
            
            Vector4<T>& operator+(Vector4<T> other){
                this->x += other.x;
                this->y += other.y;
                this->z += other.z;
                this->w += other.w;
                return *this;
            }
            
            Vector4<T>& operator* (T scale){
                this->x * scale;
                this->y * scale;
                this->z * scale;
                this->w * scale;
                return *this;
            }
            
            
            void print(){
                std::cout << x << " " << y << " " << z << " " << w << "\n";
            }
            
            T dotProduct(Vector4<T> other){
                return(this->x * other.x + this->y * other.y + this->z * other.z * this->w * other.w);
            }
            
            T lenght(){
                return sqrt(pow(x,2) + pow(y,2) + pow(z, 2) + pow(w,2));
            }
            
            
        };
    }
}

#endif