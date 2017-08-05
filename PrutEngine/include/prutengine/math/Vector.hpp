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
            protected:
            std::array<T, size> data;
            private:
            void setArguments(const size_t& pos, const T& end){
                data[pos] = end;
            }
            template<typename... Arguments>
            void setArguments(const size_t& pos, const T& fst, Arguments... tail ){
            
                data[pos] = fst;
                setArguments(pos + 1,tail...);
            }
 
            public:
            template<typename... Arguments>
            Vector(Arguments... tail){
                this->setArguments(0, tail...);
            }

            Vector(){
                static_assert(size != 0, "You can't have a vector with a size of zero!");
            }

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
                static_assert(size >=  Globals::VECTOR_X_POSITION + 1, "This vector doesn't contain a X value");
                this->data[Globals::VECTOR_X_POSITION] = x;
            }

            void setY(const T& y){
                static_assert(size >=  Globals::VECTOR_Y_POSITION + 1, "This vector doesn't contain a Y value");
                this->data[Globals::VECTOR_Y_POSITION] = y;
            }
            
            void setZ(const T& z){
                static_assert(size >=  Globals::VECTOR_Z_POSITION + 1, "This vector doesn't contain a Z value");
                this->data[Globals::VECTOR_Z_POSITION] = z;
            }

            void setW(const T& w){
                static_assert(size >=  Globals::VECTOR_W_POSITION + 1, "This vector doesn't contain a W value");
                this->data[Globals::VECTOR_W_POSITION] = w;
            }

            T getX() const {
                static_assert(size >=  Globals::VECTOR_X_POSITION + 1, "This vector doesn't contain a X value");
                return this->data[Globals::VECTOR_X_POSITION];
            }

            T getY() const {
                static_assert(size >=  Globals::VECTOR_Y_POSITION + 1, "This vector doesn't contain a Y value");
                return this->data[Globals::VECTOR_Y_POSITION];
            }

            T getZ() const {
                static_assert(size >=  Globals::VECTOR_Z_POSITION + 1, "This vector doesn't contain a Z value");
                return this->data[Globals::VECTOR_Z_POSITION];
            }

            T getW() const {
                static_assert(size >=  Globals::VECTOR_W_POSITION + 1, "This vector doesn't contain a W value");
                return this->data[Globals::VECTOR_W_POSITION];
            }



        };
       
        typedef Vector<float, 2> Vector2f;
        
        typedef Vector<float, 3> Vector3f;

        typedef Vector<float, 4> Vector4f;

        
    }
}



#endif