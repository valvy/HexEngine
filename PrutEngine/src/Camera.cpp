#include "prutengine/Camera.hpp"
#include "prutengine/AssetManager.hpp"
#include "prutengine/math/Matrix4x4.hpp"
#include "prutengine/math/Utilities.hpp"
#include "prutengine/Application.hpp"
#include "prutengine/math/Quaternion.hpp"
using namespace PrutEngine;
using namespace PrutEngine::Math;

Camera::Camera(const Vector<float,3>& startPos){
    this->transform->setPosition(startPos);
    this->transform->rotate(Vector3f(0,1,0), 0);
    // this->rotate(Vector<float,3>(0,1,0), 0);
}



void Camera::update(const float& tpf){
    const Graphics_Engine engine = Application::getInstance()->getGraphicsController()->getCurrentGraphicsEngine();
    
    if(engine == Graphics_Engine::AppleMetal){
        return;
    }
    
    const Matrix4x4<GLfloat> projection = Matrix4x4<GLfloat>::multiply(
                                                            Quaternion<GLfloat>::quaternionToMatrix(this->transform->getQuaternion()),Math::perspective<GLfloat>(45, 4.0f / 3.0f , 1, 100));
    const Matrix4x4<GLfloat> position = Matrix4x4<GLfloat>::translate(Matrix4x4<GLfloat>::identityMatrix(), this->transform->getPosition());
    
    auto assetManager =  Application::getInstance()->getAssetManager();

    for(const GLuint p : assetManager->allPrograms()){
        glUseProgram(p);
        glUniformMatrix4fv(glGetUniformLocation(p, "projection_matrix"), 1, GL_FALSE, &projection.getRawData()[0]);
        glUniformMatrix4fv(glGetUniformLocation(p, "cam_matrix"), 1, GL_TRUE, &position.getRawData()[0]);
        
    }
    
}
