#ifndef PRUTENGINE_MATH_QUATERNION_HPP
#define PRUTENGINE_MATH_QUATERNION_HPP
#include "./Vector3.hpp"
#include "./Vector4.hpp"
#include "./Matrix4x4.hpp"
#include <math.h>

namespace PrutEngine{
    namespace Math{
        template<typename T>
        struct Quaternion{
            Vector3<T> imaginary;
            T real;
            
        public:
            Quaternion(){
                this->imaginary = Vector3<T>(0,1,0);
                this->real = 0;
            }
            
            Quaternion(const Quaternion<T> &quaternion){
                this->imaginary = quaternion.imaginary;
                this->real = quaternion.real;
            }
            
            Quaternion(const Vector4<T> vec){
                this->imaginary = Vector3<T>(vec.y,vec.z,vec.w);
                this->real = vec.x;
            }
            
            bool operator==(const Quaternion<T> &quaternion){
                return quaternion.real == this->real && this->imaginary == quaternion.imaginary;
            }
            
            Quaternion& operator=(const Quaternion<T> &quat){
                this->imaginary = quat.imaginary;
                this->real = quat.real;
                return *this;
            }
            
            static Vector3<T> multiply(const Quaternion<T> &quat, const Vector3<T>& vec){
                Quaternion tmp;
                tmp.real = 0;
                tmp.imaginary = Vector3<T>::unitVector(vec);
                tmp = Quaternion<T>::multiply(quat, Quaternion::multiply(tmp, Quaternion::conjugate(quat)));
                return tmp.imaginary;
            }
            
            static Quaternion<T> multiply(const Quaternion<T> &quat1, const Quaternion<T> &quat2){
                return Quaternion<T>(Vector4<T>(
                                                quat1.real * quat2.real - quat1.imaginary.x * quat2.imaginary.x - quat1.imaginary.y * quat2.imaginary.y - quat1.imaginary.z * quat2.imaginary.z,
                                                quat1.real * quat2.imaginary.x + quat1.imaginary.x * quat2.real + quat1.imaginary.y * quat2.imaginary.z - quat1.imaginary.z * quat2.imaginary.y,
                                                quat1.real * quat2.imaginary.y - quat1.imaginary.x * quat2.imaginary.z + quat1.imaginary.y * quat2.real + quat1.imaginary.z * quat2.imaginary.x,
                                                quat1.real * quat2.imaginary.z + quat1.imaginary.x * quat2.imaginary.y - quat1.imaginary.y * quat2.imaginary.x + quat1.imaginary.z * quat2.real
                                                    ));
            }
            
            
            Quaternion<T>& operator*(const Quaternion<T> &quat){
                return &Quaternion::multiply(this,quat);
            }
            
            Quaternion<T>& operator*=(const Quaternion<T> &quat){
                this = Quaternion::multiply(this, quat);
                return *this;
            }
            
            static Quaternion<T> conjugate(const Quaternion<T> &quat){
                return Quaternion<T>(Vector4<T>(
                                            quat.real,
                                            -quat.imaginary.x,
                                            -quat.imaginary.y,
                                            -quat.imaginary.z
                                ));
            }
            
            T normalize(){
                return 1 / sqrt(real * real +
                                imaginary.x * imaginary.x +
                                imaginary.y * imaginary.y +
                                imaginary.z * imaginary.z
                                );
            }
            
            static Matrix4x4<T> quaternionToMatrix(const Quaternion& q){
                Quaternion tmp(q);
                T normalize = tmp.normalize();
                tmp.real *= normalize;
                tmp.imaginary.x *= normalize;
                tmp.imaginary.y *= normalize;
                tmp.imaginary.z *= normalize;
                const T qx = tmp.imaginary.x;
                const T qy = tmp.imaginary.y;
                const T qz = tmp.imaginary.z;
                const T qw = tmp.real;
                return Matrix4x4<T>(
                            Vector4<T>(1 - 2*qy*qy - 2*qz*qz, 2*qx*qy - 2*qz*qw, 2*qx*qz + 2*qy*qw, 0),
                            Vector4<T>(2*qx*qy + 2*qz*qw, 1 - 2*qx*qx - 2*qz*qz, 2*qy*qz - 2*qx*qw, 0),
                            Vector4<T>(2*qx*qz - 2*qy*qw, 2*qy*qz + 2*qx*qw, 1 - 2*qx*qx - 2*qy*qy, 0),
                            Vector4<T>(0,0,0,1));
                
            }
            
            static Quaternion<T> rotate(const Quaternion<T> &q, const Vector3<T> &rot, T angle){
                if(rot.x == 0 && rot.y == 0 && rot.z == 0){
                    return Quaternion();
                }
                
                Vector3<T> unitv = Vector3<T>::unitVector(rot);
                Quaternion tmp(q);
                T normalize = tmp.normalize();
                tmp.real *= normalize;
                tmp.imaginary.x *= normalize;
                tmp.imaginary.y *= normalize;
                tmp.imaginary.z *= normalize;
                const T degrees = (angle * Math::PI) / 180;
                const T halfSin = sin(degrees / 2);
                
                return Quaternion::multiply(Quaternion(Vector4<T>(cos(degrees / 2),
                                                                halfSin * unitv.x,
                                                                halfSin * unitv.y,
                                                                halfSin * unitv.z)), tmp);
            }

        };

        
    }
}
#endif
