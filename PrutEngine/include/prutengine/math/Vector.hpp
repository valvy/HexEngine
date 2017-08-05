#ifndef PRUTENGINE_MATH_VECTOR_HPP
#define PRUTENGINE_MATH_VECTOR_HPP
#include <array>
#include <cmath>

namespace PrutEngine{
    namespace Math{
        namespace Globals{
            constexpr size_t VECTOR_X_POSITION = 0;
            constexpr size_t VECTOR_Y_POSITION = 1;
            constexpr size_t VECTOR_Z_POSITION = 2;
            constexpr size_t VECTOR_W_POSITION = 3;
        }


        template<typename T, size_t size>
        class Vector{
            private:

            protected:
            std::array<T, size> data;
            public:

            Vector<T,size> operator*(const T& number){
                for(size_t i = 0; i < size; i++){
                    data[i] *= number;
                }
            }

            Vector<T,size>& operator*=(const T& number){
                
            }

            void set(const Vector<T,size>& dat){
                for(size_t i = 0; i < size; i++){
                    this->data[i] = dat.data[i];
                }
            }

            T length() const {
                T result = 0;
                for(size_t i = 0; i < size; i++){
                    result += std::pow(2,data[0]);
                }


                return std::sqrt(result);
            }

            Vector<T, size> unitVector() const {
                const T length = 1 / this->length();
                Vector<T,size> result;
                for(size_t i = 0; i < size; i++){
                    result.data[i] = this->data[i] * length;
                }
                
                return result;

            }

            void setX(const T& x){
                this->data[Globals::VECTOR_X_POSITION] = x;
            }

            void setY(const T& y){
                this->data[Globals::VECTOR_Y_POSITION] = y;
            }
            
            void setZ(const T& z){
                this->data[Globals::VECTOR_Z_POSITION] = z;
            }

            void setW(const T& w){
                this->data[Globals::VECTOR_W_POSITION] = w;
            }

            T getX() const {
                return this->data[Globals::VECTOR_X_POSITION];
            }

            T getY() const {
                return this->data[Globals::VECTOR_Y_POSITION];
            }

            T getZ() const {
                return this->data[Globals::VECTOR_Z_POSITION];
            }

            T getW() const {
                return this->data[Globals::VECTOR_W_POSITION];
            }



        };

        template<typename T>
        struct Vector2 : public Vector<T, 2>{
            Vector2(){
                this->data[Globals::VECTOR_X_POSITION] = 0;
                this->data[Globals::VECTOR_Y_POSITION] = 0;
            }

            Vector2(const T& x,const T& y){
                this->data[Globals::VECTOR_X_POSITION] = x;
                this->data[Globals::VECTOR_Y_POSITION] = y;
            }

            Vector2(const Vector2<T>& vector){
                this->set(vector);
            }
        };
        
        template<typename T>
        struct Vector3 : public Vector<T, 3>{
            Vector3(){
             //   this->data[Globals::VECTOR_X_POSITION] = 0;
             //   this->data[Globals::VECTOR_Y_POSITION] = 0;
             //   this->data[Globals::VECTOR_Z_POSITION] = 0;
            }

            Vector3(const T& x, const T& y, const T& z){
                this->data[Globals::VECTOR_X_POSITION] = x;
                this->data[Globals::VECTOR_Y_POSITION] = y;
                this->data[Globals::VECTOR_Z_POSITION] = z;
            }

            Vector3(const Vector3<T>& vector){
                this->set(vector);
            }
        };

        template<typename T>
        struct Vector4 : public Vector<T, 4>{
            Vector4(){
                this->data[Globals::VECTOR_X_POSITION] = 0;
                this->data[Globals::VECTOR_Y_POSITION] = 0;
                this->data[Globals::VECTOR_Z_POSITION] = 0;
                this->data[Globals::VECTOR_W_POSITION] = 0;
            }

            Vector4(const T& x, const T& y, const T& z, const T& w){
                this->data[Globals::VECTOR_X_POSITION] = x;
                this->data[Globals::VECTOR_Y_POSITION] = y;
                this->data[Globals::VECTOR_Z_POSITION] = z;
                this->data[Globals::VECTOR_W_POSITION] = w;
            }

        
        };
        
    }
}



#endif