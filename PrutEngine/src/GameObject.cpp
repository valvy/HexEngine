#include "prutengine/GameObject.hpp"
#include "prutengine/math/Utilities.hpp"
#include <iostream>
using namespace PrutEngine;
using namespace PrutEngine::Math;

GameObject::GameObject(){
    this->setScale(Vector3<float>(1,1,1));
}

GameObject::~GameObject(){

}

void GameObject::loadTexture(std::string meshPath){
    auto assetManager =  Application::getInstance()->getAssetManager();
    this->texture = assetManager->loadTexture(meshPath);
}


void GameObject::translate(const Vector3<float>& vec, float speed){
    this->position.setX(this->position.getX() + vec.getX() * speed);
    this->position.setY(this->position.getY() + vec.getY() * speed);
    this->position.setZ(this->position.getZ() + vec.getZ() * speed);
    //this->position.x += vec.x * speed;
    //this->position.y += vec.y * speed;
    //this->position.z += vec.z * speed;
}

void GameObject::onKeyDown(unsigned short keyCode){
    //virtual
}



void GameObject::update(float tpf){
    auto assetManager =  Application::getInstance()->getAssetManager();
    
    //setup the program and mesh
    glUseProgram(program->getProgram());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,this->texture->getTexture());
    glBindVertexArray(this->mesh->getVao());
    
    //Make the calculation
    Matrix4x4<GLfloat> mat = Matrix4x4<GLfloat>::identityMatrix();
    mat = Matrix4x4<GLfloat>::scale(mat,this->scale);
    Matrix4x4<GLfloat> pos = Matrix4x4<GLfloat>::translate(Matrix4x4<GLfloat>::identityMatrix(),position);
    
    mat = Matrix4x4<GLfloat>::multiply(mat,pos);
    mat = Matrix4x4<GLfloat>::multiply(mat, Quaternion<GLfloat>::quaternionToMatrix(this->quaternion));
    
    //pass it to opengl
    glUniformMatrix4fv(this->pos_reference, 1, GL_TRUE, &mat.getRawData()[0]);
    glEnableVertexAttribArray ( 0 );
    
    glDrawArrays ( GL_TRIANGLES, 0, this->mesh->getSize());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    
}

void GameObject::rotate(const Vector3<float>& vec, float angle){
    this->quaternion = Quaternion<float>::rotate(quaternion, vec,angle);
}

void GameObject::loadMesh(std::string meshPath){
    auto assetManager =  Application::getInstance()->getAssetManager();
    this->mesh = assetManager->loadMesh(meshPath);
   
}

Quaternion<float> GameObject::getQuaternion() const{
    return this->quaternion;
}

Vector3<float> GameObject::getScale() const{
    return this->scale;
}

Vector3<float> GameObject::getPosition() const{
    return this->position;
}

void GameObject::setPosition(const Vector3<float> &position){
    this->position = position;
}

void GameObject::setScale(const Vector3<float> &scale){
    this->scale = scale;
}

void GameObject::setQuaternion(const Quaternion<float> &quat){
    this->quaternion = quat;
}
