/*
 * Copyright (c) 2015, Heiko van der Heijden
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef MATRIX4X4_HPP
#define MATRIX4X4_HPP
#include "Vector4.hpp"
#include "Vector3.hpp"
#include <cmath>
#include <vector>
#include "Utilities.hpp"


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
    Vector4<T> row1,row2,row3,row4;
    
    /*!
     *  Initializes the matrix with a identity matrix. (all zeroes except the ones diagonal)
     */
    Matrix4x4(){
        row1 = Vector4<T>(1,0,0,0);
        row2 = Vector4<T>(0,1,0,0);
        row3 = Vector4<T>(0,0,1,0);
        row4 = Vector4<T>(0,0,0,1);
    }
    
    static Matrix4x4<T> identityMatrix(){
        return Matrix4x4<T>(
                            Vector4<T>(1,0,0,0),
                            Vector4<T>(0,1,0,0),
                            Vector4<T>(0,0,1,0),
                            Vector4<T>(0,0,0,1));
    }
    

    
    Matrix4x4(const Matrix4x4<T>& other){
        this->row1 = other.row1;
        this->row2 = other.row2;
        this->row3 = other.row3;
        this->row4 = other.row4;
    }
    
    Matrix4x4(Vector4<T> r1, Vector4<T> r2, Vector4<T> r3, Vector4<T> r4){
        this->row1 = r1;
        this->row2 = r2;
        this->row3 = r3;
        this->row4 = r4;
    }
    
    /*!
     *  Translates the matrix to
     *  @param vector, The vector you wish to translate to
     */
    static Matrix4x4<T> translate(Matrix4x4<T> mat, Vector3<T> vector){
        Matrix4x4<T> result(mat);
        result.row1.w += vector.x;
        result.row2.w += vector.y;
        result.row3.w += vector.z;
        return result;
      
    }
    

    static Matrix4x4<T> setPosition(Matrix4x4<T> mat, Vector3<T> vector){
        Matrix4x4<T> result(mat);
        result.row1.w = vector.x;
        result.row2.w = vector.y;
        result.row3.w = vector.z;
        return result;
    }
    
    static Matrix4x4<T> transpose(Matrix4x4 mat){
        Matrix4x4<T> result;
        result.row1 = Vector4<T>(mat.row1.x, mat.row2.x, mat.row3.x,mat.row4.x);
        result.row2 = Vector4<T>(mat.row1.y, mat.row2.y,mat.row3.y,mat.row4.y);
        result.row3 = Vector4<T>(mat.row1.z, mat.row2.z, mat.row3.z,mat.row4.z);
        result.row4 = Vector4<T>(mat.row1.w, mat.row2.w,mat.row3.w,mat.row4.w);
        return result;
        
    }

    
    static Vector3<T> multiply(const Matrix4x4<T>& mat, const Vector3<T> vec){
        return Vector3<T>(
                          mat.row1.x * vec.x + mat.row1.y * vec.y + mat.row1.z * vec.z,
                          mat.row2.x * vec.x + mat.row2.y * vec.y + mat.row2.z * vec.z,
                          mat.row3.x * vec.x + mat.row3.y * vec.y + mat.row3.z * vec.z);
    }
    
    /*!
     *  Multiplies a matrix with an other matrix
     *  @param other, the matrix you wish to multiply with
     */
    static Matrix4x4<T> multiply(const Matrix4x4<T>& first,const Matrix4x4<T>& other){
        //generate temporary matrix
        Matrix4x4<T> result;
        //Row 1
        result.row1.x = first.row1.x * other.row1.x + first.row1.y * other.row2.x + first.row1.z * other.row3.x + first.row1.w * other.row4.x;
        result.row1.y = first.row1.x * other.row1.y + first.row1.y * other.row2.y + first.row1.z * other.row3.y + first.row1.w * other.row4.y;
        result.row1.z = first.row1.x * other.row1.z + first.row1.y * other.row2.z + first.row1.z * other.row3.z + first.row1.w * other.row4.z;
        result.row1.w = first.row1.x * other.row1.w + first.row1.y * other.row2.w + first.row1.z * other.row3.w + first.row1.w * other.row4.w;
        
        //Row2
        result.row2.x = first.row2.x * other.row1.x + first.row2.y * other.row2.x + first.row2.z * other.row3.x + first.row2.w * other.row4.x;
        result.row2.y = first.row2.x * other.row1.y + first.row2.y * other.row2.y + first.row2.z * other.row3.y + first.row2.w * other.row4.y;
        result.row2.z = first.row2.x * other.row1.z + first.row2.y * other.row2.z + first.row2.z * other.row3.z + first.row2.w * other.row4.z;
        result.row2.w = first.row2.x * other.row1.w + first.row2.y * other.row2.w + first.row2.z * other.row3.w + first.row2.w * other.row4.w;
        
        //Row3
        result.row3.x = first.row3.x * other.row1.x + first.row3.y * other.row2.x + first.row3.z * other.row3.x + first.row3.w * other.row4.x;
        result.row3.y = first.row3.x * other.row1.y + first.row3.y * other.row2.y + first.row3.z * other.row3.y + first.row3.w * other.row4.y;
        result.row3.z = first.row3.x * other.row1.z + first.row3.y * other.row2.z + first.row3.z * other.row3.z + first.row3.w * other.row4.z;
        result.row3.w = first.row3.x * other.row1.w + first.row3.y * other.row2.w + first.row3.z * other.row3.w + first.row3.w * other.row4.w;
        
        //Row4
        result.row4.x = first.row4.x * other.row1.x + first.row4.y * other.row2.x + first.row4.z * other.row3.x + first.row4.w * other.row4.x;
        result.row4.y = first.row4.x * other.row1.y + first.row4.y * other.row2.y + first.row4.z * other.row3.y + first.row4.w * other.row4.y;
        result.row4.z = first.row4.x * other.row1.z + first.row4.y * other.row2.z + first.row4.z * other.row3.z + first.row4.w * other.row4.z;
        result.row4.w = first.row4.x * other.row1.w + first.row4.y * other.row2.w + first.row4.z * other.row3.w + first.row4.w * other.row4.w;
        
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
        angle = angle * Math::PI / 180; //convert degrees to radians
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

    }
    

    void print(){
        std::cout <<"\n\n";
        row1.print();
        row2.print();
        row3.print();
        row4.print();
    }
    
    /*!
     *  Get all the data in an Vector
     *  @return rawData The vector with all the row data
     */
    std::vector<T> getRawData() const{
        return{
            row1.x,row1.y,row1.z,row1.w,
            row2.x,row2.y,row2.z,row2.w,
            row3.x,row3.y,row3.z,row3.w,
            row4.x,row4.y,row4.z,row4.w
        };
    }
    
    
    /*!
     *  Scales the matrix with given vector
     *  @param s The vector you wish to scale with
     */
    static Matrix4x4<T> scale(const Matrix4x4<T>& mat, const Vector3<T>& s){
        Matrix4x4<T> tmp(mat);
        tmp.row1.x *= s.x;
        tmp.row2.y *= s.y;
        tmp.row3.z *= s.z;
        return tmp;
    }
    

    
};

#endif
