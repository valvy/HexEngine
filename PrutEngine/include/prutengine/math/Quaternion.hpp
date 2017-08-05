#ifndef PRUTENGINE_MATH_QUATERNION_HPP
#define PRUTENGINE_MATH_QUATERNION_HPP
//#include "./Vector3.hpp"
//#include "./Vector4.hpp"
#include "./Vector.hpp"
#include "./Matrix4x4.hpp"
#include <math.h>

namespace PrutEngine{
    namespace Math{
        template<typename T>
        struct Quaternion{
            Vector<T,3> imaginary;
            T real;
            
        public:
            Quaternion(){
                this->imaginary = Vector<T,3>(0,1,0);
                this->real = 0;
            }
            
            Quaternion(const Quaternion<T> &quaternion){
                this->imaginary = quaternion.imaginary;
                this->real = quaternion.real;
            }
            
            Quaternion(const Vector<T,4> vec){
                this->imaginary = Vector<T,3>(vec.getY(),vec.getZ(),vec.getW());
                this->real = vec.getX();
            }
            
            bool operator==(const Quaternion<T> &quaternion){
                return quaternion.real == this->real && this->imaginary == quaternion.imaginary;
            }
            
            Quaternion& operator=(const Quaternion<T> &quat){
                this->imaginary = quat.imaginary;
                this->real = quat.real;
                return *this;
            }
            
            static Vector<T,3> multiply(const Quaternion<T> &quat, const Vector<T,3>& vec){
                Quaternion tmp;
                tmp.real = 0;
                tmp.imaginary = vec.unitVector();
                //Vector3<T>::unitVector(vec);
                tmp = Quaternion<T>::multiply(quat, Quaternion::multiply(tmp, Quaternion::conjugate(quat)));
                return tmp.imaginary;
            }
            
            static Quaternion<T> multiply(const Quaternion<T> &quat1, const Quaternion<T> &quat2){
                return Quaternion<T>(Vector<T,4>(
                                                quat1.real * quat2.real - quat1.imaginary.getX() * quat2.imaginary.getX() - quat1.imaginary.getY() * quat2.imaginary.getY() - quat1.imaginary.getZ() * quat2.imaginary.getZ(),
                                                quat1.real * quat2.imaginary.getX() + quat1.imaginary.getX() * quat2.real + quat1.imaginary.getY() * quat2.imaginary.getZ() - quat1.imaginary.getZ() * quat2.imaginary.getY(),
                                                quat1.real * quat2.imaginary.getY() - quat1.imaginary.getX() * quat2.imaginary.getZ() + quat1.imaginary.getY() * quat2.real + quat1.imaginary.getZ() * quat2.imaginary.getX(),
                                                quat1.real * quat2.imaginary.getZ() + quat1.imaginary.getX() * quat2.imaginary.getY() - quat1.imaginary.getY() * quat2.imaginary.getX() + quat1.imaginary.getZ() * quat2.real
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
                return Quaternion<T>(Vector<T,4>(
                                            quat.real,
                                            -quat.imaginary.getX(),
                                            -quat.imaginary.getY(),
                                            -quat.imaginary.getZ()
                                ));
            }
            
            T normalize(){
                return 1 / sqrt(real * real +
                                imaginary.getX() * imaginary.getX() +
                                imaginary.getY() * imaginary.getY() +
                                imaginary.getZ() * imaginary.getZ()
                                );
            }
            
            static Matrix4x4<T> quaternionToMatrix(const Quaternion& q){
                Quaternion tmp(q);
                T normalize = tmp.normalize();
                tmp.real *= normalize;
                tmp.imaginary.setX(tmp.imaginary.getX() * normalize);
                tmp.imaginary.setY(tmp.imaginary.getY() * normalize);
                tmp.imaginary.setZ(tmp.imaginary.getZ() * normalize);

                const T qx = tmp.imaginary.getX();
                const T qy = tmp.imaginary.getY();
                const T qz = tmp.imaginary.getZ();
                const T qw = tmp.real;
                return Matrix4x4<T>(
                            Vector<T,4>(1 - 2*qy*qy - 2*qz*qz, 2*qx*qy - 2*qz*qw, 2*qx*qz + 2*qy*qw, 0),
                            Vector<T,4>(2*qx*qy + 2*qz*qw, 1 - 2*qx*qx - 2*qz*qz, 2*qy*qz - 2*qx*qw, 0),
                            Vector<T,4>(2*qx*qz - 2*qy*qw, 2*qy*qz + 2*qx*qw, 1 - 2*qx*qx - 2*qy*qy, 0),
                            Vector<T,4>(0,0,0,1));
                
            }
            
            static Quaternion<T> rotate(const Quaternion<T> &q, const Vector<T, 3> &rot, T angle){
              //  return Quaternion();
                if(rot.getX() == 0 && rot.getY() == 0 && rot.getZ() == 0){
                    return Quaternion();
                }
                
                Vector<T, 3> unitv = rot.unitVector();
                //Vector3<T>::unitVector(rot);
                Quaternion tmp(q);
                T normalize = tmp.normalize();
                tmp.real *= normalize;
                tmp.imaginary.setX(tmp.imaginary.getX() * normalize);
                tmp.imaginary.setY(tmp.imaginary.getY() * normalize);
                tmp.imaginary.setZ(tmp.imaginary.getZ() * normalize);
              //  tmp.imaginary.x *= normalize;
              //  tmp.imaginary.y *= normalize;
              //  tmp.imaginary.z *= normalize;
                const T degrees = (angle * Math::PI) / 180;
                const T halfSin = sin(degrees / 2);
                
                return Quaternion::multiply(Quaternion(Vector<T,4>(cos(degrees / 2),
                                                                halfSin * unitv.getX(),
                                                                halfSin * unitv.getY(),
                                                                halfSin * unitv.getZ())), tmp);
            }

        };

        
    }
}
#endif
