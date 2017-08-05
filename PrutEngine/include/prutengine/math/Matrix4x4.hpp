#ifndef PRUTENGINE_MATH_MATRIX4X4_HPP
#define PRUTENGINE_MATH_MATRIX4X4_HPP
#include "./Vector.hpp"
#include <cmath>
#include <vector>
#include "Utilities.hpp"

namespace PrutEngine{
    namespace Math{
        enum class Axis{
            X,
            Y,
            Z,
        };
    
        /*! A 4 by 4 matrix data type
        *  @author Heiko van der Heijden
        *  This struct manages a 4 by 4 matrix.. and has all the basic calculations required by opengl
        */
        template<typename T>
        struct Matrix4x4{
            /*!
            *  All the rows stored in a Vector4, this is done so there are never any problems
            *  With the length and order of the Matrix
            */
            Vector<T,4> row1,row2,row3,row4;
            
            /*!
            *  Initializes the matrix with a identity matrix. (all zeroes except the ones diagonal)
            */
            Matrix4x4(){
                row1 = Vector<T,4>(1,0,0,0);
                row2 = Vector<T,4>(0,1,0,0);
                row3 = Vector<T,4>(0,0,1,0);
                row4 = Vector<T,4>(0,0,0,1);
            }
            
            static Matrix4x4<T> identityMatrix(){
                return Matrix4x4<T>(
                                    Vector<T,4>(1,0,0,0),
                                    Vector<T,4>(0,1,0,0),
                                    Vector<T,4>(0,0,1,0),
                                    Vector<T,4>(0,0,0,1));
            }
            

            
            Matrix4x4(const Matrix4x4<T>& other){
                this->row1 = other.row1;
                this->row2 = other.row2;
                this->row3 = other.row3;
                this->row4 = other.row4;
            }
            
            Matrix4x4(Vector<T,4> r1, Vector<T,4> r2, Vector<T,4> r3, Vector<T,4> r4){
                this->row1 = r1;
                this->row2 = r2;
                this->row3 = r3;
                this->row4 = r4;
            }
            
            /*!
            *  Translates the matrix to
            *  @param vector, The vector you wish to translate to
            */
            static Matrix4x4<T> translate(Matrix4x4<T> mat, Vector<T,3> vector){
                Matrix4x4<T> result(mat);
                result.row1.setW(result.row1.getW() + vector.getX());
                result.row2.setW(result.row2.getW() + vector.getY());
                result.row3.setW(result.row3.getW() + vector.getZ());

                return result;
            
            }
            

            static Matrix4x4<T> setPosition(Matrix4x4<T> mat, Vector<T,3> vector){
                Matrix4x4<T> result(mat);
                result.row1.setW(vector.getX());
                result.row2.setW(vector.getY());
                result.row3.setW(vector.getZ());
                return result;
            }
            
            static Matrix4x4<T> transpose(Matrix4x4 mat){
                Matrix4x4<T> result;
                result.row1 = Vector<T,4>(mat.row1.getX(), mat.row2.getX(), mat.row3.getX(),mat.row4.getX());
                result.row2 = Vector<T,4>(mat.row1.getY(), mat.row2.getY(),mat.row3.getY(),mat.row4.getY());
                result.row3 = Vector<T,4>(mat.row1.getZ(), mat.row2.getZ(), mat.row3.getZ(),mat.row4.getZ());
                result.row4 = Vector<T,4>(mat.row1.getW(), mat.row2.getW(),mat.row3.getW(),mat.row4.getW());
                return result;
                
            }

            
            static Vector<T,3> multiply(const Matrix4x4<T>& mat, const Vector<T,3> vec){
                return Vector<T,3>(
                                mat.row1.getX() * vec.getX() + mat.row1.getY() * vec.getY() + mat.row1.getZ() * vec.getZ(),
                                mat.row2.getX() * vec.getX() + mat.row2.getY() * vec.getY() + mat.row2.getZ() * vec.getZ(

                                ),
                                mat.row3.getX() * vec.getX() + mat.row3.getY() * vec.getY() + mat.row3.getZ() * vec.getZ());
            }
            
            /*!
            *  Multiplies a matrix with an other matrix
            *  @param other, the matrix you wish to multiply with
            */
            static Matrix4x4<T> multiply(const Matrix4x4<T>& first,const Matrix4x4<T>& other){
                //generate temporary matrix
                Matrix4x4<T> result;
                
                //Row 1
                result.row1.setX(first.row1.getX() * other.row1.getX() + first.row1.getY() * other.row2.getX() + first.row1.getZ() * other.row3.getX() + first.row1.getW() * other.row4.getX());
                result.row1.setY(first.row1.getX() * other.row1.getY() + first.row1.getY() * other.row2.getY() + first.row1.getZ() * other.row3.getY() + first.row1.getW() * other.row4.getY());
                result.row1.setZ(first.row1.getX() * other.row1.getZ() + first.row1.getY() * other.row2.getZ() + first.row1.getZ() * other.row3.getZ() + first.row1.getW() * other.row4.getZ());
                result.row1.setW(first.row1.getX() * other.row1.getW() + first.row1.getY() * other.row2.getW() + first.row1.getZ() * other.row3.getW() + first.row1.getW() * other.row4.getW());

                //Row2
                result.row2.setX(first.row2.getX() * other.row1.getX() + first.row2.getY() * other.row2.getX() + first.row2.getZ() * other.row3.getX() + first.row2.getW() * other.row4.getX());
                result.row2.setY(first.row2.getX() * other.row1.getY() + first.row2.getY() * other.row2.getY() + first.row2.getZ() * other.row3.getY() + first.row2.getW() * other.row4.getY());
                result.row2.setZ(first.row2.getX() * other.row1.getZ() + first.row2.getY() * other.row2.getZ() + first.row2.getZ() * other.row3.getZ() + first.row2.getW() * other.row4.getZ());
                result.row2.setW(first.row2.getX() * other.row1.getW() + first.row2.getY() * other.row2.getW() + first.row2.getZ() * other.row3.getW() + first.row2.getW() * other.row4.getW());
                
                //Row3
                result.row3.setX(first.row3.getX() * other.row1.getX() + first.row3.getY() * other.row2.getX() + first.row3.getZ() * other.row3.getX() + first.row3.getW() * other.row4.getX());
                result.row3.setY(first.row3.getX() * other.row1.getY() + first.row3.getY() * other.row2.getY() + first.row3.getZ() * other.row3.getY() + first.row3.getW() * other.row4.getY());
                result.row3.setZ(first.row3.getX() * other.row1.getZ() + first.row3.getY() * other.row2.getZ() + first.row3.getZ() * other.row3.getZ() + first.row3.getW() * other.row4.getZ());
                result.row3.setW(first.row3.getX() * other.row1.getW() + first.row3.getY() * other.row2.getW() + first.row3.getZ() * other.row3.getW() + first.row3.getW() * other.row4.getW());
                
                //Row4
                result.row4.setX(first.row4.getX() * other.row1.getX() + first.row4.getY() * other.row2.getX() + first.row4.getZ() * other.row3.getX() + first.row4.getW() * other.row4.getX());
                result.row4.setY(first.row4.getX() * other.row1.getY() + first.row4.getY() * other.row2.getY() + first.row4.getZ() * other.row3.getY() + first.row4.getW() * other.row4.getY());
                result.row4.setZ(first.row4.getX() * other.row1.getZ() + first.row4.getY() * other.row2.getZ() + first.row4.getZ() * other.row3.getZ() + first.row4.getW() * other.row4.getZ());
                result.row4.setW(first.row4.getX() * other.row1.getW() + first.row4.getY() * other.row2.getW() + first.row4.getZ() * other.row3.getW() + first.row4.getW() * other.row4.getW());
                
                return result;
            }
            
            Matrix4x4<T> operator*(Matrix4x4<T> other) const{
                return Matrix4x4::multiply(*this, other);
            }
            
            /*!
            *  set the data from the other matrix in itself
            *  @param other, the matrix you wish to set as this
            */
            Matrix4x4<T>& operator=(Matrix4x4 other){
                this->row1 = other.row1;
                this->row2 = other.row2;
                this->row3 = other.row3;
                this->row4 = other.row4;
                return *this;
            }
            
            Matrix4x4<T>& operator*=(Matrix4x4 other){
                Matrix4x4 <T> result = Matrix4x4<T>(row1,row2,row3,row4) * other;
                this->row1 = result.row1;
                this->row2 = result.row2;
                this->row3 = result.row3;
                this->row4 = result.row4;
                
                return *this;
            }
            
            
            
            /*!
            *  Rotates the matrix around an given axis.
            *  @param angle, the degrees you want to rotate
            *  @param axis, The axis you wish to rotate around
            */
            static Matrix4x4<T> rotate(T angle, Axis axis){
                /*angle = angle * Math::PI / 180; //convert degrees to radians
                Matrix4x4<T> result;
                switch(axis){
                    case Axis::X:
                        result.row2.y = cos(angle); result.row2.z = sin(angle);
                        result.row3.y = -sin(angle); result.row3.z = cos(angle);
                        return result;
                    case Axis::Y:
                        result.row1.x = cos(angle); result.row1.z = sin(angle);
                        result.row3.x = -sin(angle); result.row3.z = cos(angle);
                        return result;
                    case Axis::Z:
                        result.row1.x = cos(angle); result.row1.y = sin(angle);
                        result.row2.y = -sin(angle); result.row2.y = cos(angle);
                        return result;
                }
                return result;*/
                throw "Not supported";

            }
            


            /*!
            *  Get all the data in an Vector
            *  @return rawData The vector with all the row data
            */
            std::vector<T> getRawData() const{
                return{
                    row1.getX(),row1.getY(),row1.getZ(),row1.getW(),
                    row2.getX(),row2.getY(),row2.getZ(),row2.getW(),
                    row3.getX(),row3.getY(),row3.getZ(),row3.getW(),
                    row4.getX(),row4.getY(),row4.getZ(),row4.getW()
                };
            }
            
            
            /*!
            *  Scales the matrix with given vector
            *  @param s The vector you wish to scale with
            */
            static Matrix4x4<T> scale(const Matrix4x4<T>& mat, const Vector<T,3>& s){
                Matrix4x4<T> tmp(mat);
                //T x, y , z;
                const T x = tmp.row1.getX() * s.getX();
                const T y = tmp.row2.getY() * s.getY();
                const T z = tmp.row3.getZ() * s.getZ();
                tmp.row1.setX(x);
                tmp.row2.setY(y);
                tmp.row3.setZ(z);

                return tmp;
            }
            

            
        };
    }
}

#endif
