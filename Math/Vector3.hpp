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

#ifndef VECTOR3_HPP
#define VECTOR3_HPP
#include <math.h>
#include <sstream>
template<typename T>
struct Vector3{
    T x, y, z;
    Vector3(T x, T y, T z) : x(x), y(y), z(z){};
    Vector3(){}
    
    T lenght(){
        return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
    }
    
    Vector3<T>& operator* (T scale){
        this->x * scale;
        this->y * scale;
        this->z * scale;
        return *this;
    }
    
    Vector3<T>& operator- (const Vector3<T>& other){
        Vector3<T> result;
        result.x = this->x + (-1 * other.x);
        result.y = this->y + (-1 * other.y);
        result.z = this->z + (-1 * other.z);
        return result;
    }
    
    Vector3<T>& operator=(const Vector3<T>& other){
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
        return *this;
        
    }
    
    bool operator==(Vector3<T> other){
        return(this->x == other.x
               && this->y == other.y
               && this->z == other.z);
    }
/*
    
    std::ostream& operator<<(std::ostream& ost, const Vector3<T>& vector){
        ost << vector.x << " " << vector.y << " " << vector.z;
        return ost;
    }
    */
    T dotProduct(const Vector3<T> &other){
        return (this->x * other.x + this->y * other.y + this->z * other.z);
    }
    
    static Vector3<T> unitVector(const Vector3<T> &vec){
        T length = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
        if(length != 1 && length != 0){
            length = (1.0 / sqrt(length));
            return Vector3<T>(vec.x * length, vec.y * length, vec.z * length);
        }else{
            return Vector3<T>(vec);
        }
    }
    
    Vector3<T> crossProduct(const Vector3<T> &other){
        Vector3<T> result;
        result.x = this->y * other.z - this->z * other.y;
        result.y = this->z * other.x - this->x * other.z;
        result.z = this->x * other.y - this->y * other.x;
        return result;
    }
};
#endif