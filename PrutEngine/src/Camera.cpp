#include "prutengine/Camera.hpp"
#include "prutengine/AssetManager.hpp"
#include "prutengine/math/Matrix4x4.hpp"
#include "prutengine/math/Utilities.hpp"
#include "prutengine/math/Quaternion.hpp"
using namespace PrutEngine;
using namespace PrutEngine::Math;

Camera::Camera(const Vector<float,3>& startPos){
    this->setPosition(startPos);
    this->rotate(Vector<float,3>(0,1,0), 0);
}

void Camera::setPosition(const Vector<float,3> &position){
   // GameObject::setPosition(position);
    this->getTransform()->setPosition(position);
}

void Camera::rotate(const Vector<float,3>& vec, float angle){
    this->getTransform()->rotate(vec, angle);
}

void Camera::setQuaternion(const Quaternion<float>& quat){
    this->getTransform()->setQuaternion(quat);
}

void Camera::translate(const Vector<float,3>& vec, float speed){
    this->getTransform()->translate(vec, speed);
}


void Camera::onKeyDown(unsigned short keycode){
    //virtual
}

Quaternion<float> Camera::getQuaternion() const{
    return this->getTransform()->getQuaternion();
    //return GameObject::getQuaternion();
}

Vector<float,3> Camera::getPosition() const{
    return this->getTransform()->getPosition();
    // return GameObject::getPosition();
}

void Camera::update(float tpf){
    const Graphics_Engine engine = Application::getInstance()->getGraphicsController()->getCurrentGraphicsEngine();
    
    if(engine == Graphics_Engine::AppleMetal){
        return;
    }
    
    const Matrix4x4<GLfloat> projection = Matrix4x4<GLfloat>::multiply(
                                                            Quaternion<GLfloat>::quaternionToMatrix(this->getQuaternion()),Math::perspective<GLfloat>(45, 4.0f / 3.0f , 1, 100));
    const Matrix4x4<GLfloat> position = Matrix4x4<GLfloat>::translate(Matrix4x4<GLfloat>::identityMatrix(), getPosition());
    
    auto assetManager =  Application::getInstance()->getAssetManager();

    for(const GLuint p : assetManager->allPrograms()){
        glUseProgram(p);
        glUniformMatrix4fv(glGetUniformLocation(p, "projection_matrix"), 1, GL_FALSE, &projection.getRawData()[0]);
        glUniformMatrix4fv(glGetUniformLocation(p, "cam_matrix"), 1, GL_TRUE, &position.getRawData()[0]);
        
    }
    
}
