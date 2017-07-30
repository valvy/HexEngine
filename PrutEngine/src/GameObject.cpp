#include "prutengine/GameObject.hpp"
#include "prutengine/math/Utilities.hpp"

using namespace PrutEngine;
using namespace PrutEngine::Math;

GameObject::GameObject(){
    this->setScale(Vector3<float>(1,1,1));
}

GameObject::~GameObject(){
    
}

void GameObject::loadTexture(std::string meshPath){
    this->texture = AssetManager::loadTexture(meshPath);
}

void GameObject::onClick(){
    //virtual
}

void GameObject::translate(const Vector3<float>& vec, float speed){
    this->position.x += vec.x * speed;
    this->position.y += vec.y * speed;
    this->position.z += vec.z * speed;
}

void GameObject::onKeyDown(unsigned short keyCode){
    //virtual
}

void GameObject::onScroll(float velocityX, float velocityY){
    //virtual
}

void GameObject::update(float tpf){

    
    //setup the program and mesh
    glUseProgram(AssetManager::getProgram(this->program));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,AssetManager::getTexture(this->texture));
    glBindVertexArray(AssetManager::getMesh(this->mesh)->getVao());
    
    //Make the calculation
    Matrix4x4<GLfloat> mat = Matrix4x4<GLfloat>::identityMatrix();
    mat = Matrix4x4<GLfloat>::scale(mat,this->scale);
    Matrix4x4<GLfloat> pos = Matrix4x4<GLfloat>::translate(Matrix4x4<GLfloat>::identityMatrix(),position);
    
    mat = Matrix4x4<GLfloat>::multiply(mat,pos);
    mat = Matrix4x4<GLfloat>::multiply(mat, Quaternion<GLfloat>::quaternionToMatrix(this->quaternion));
    
    //pass it to opengl
    glUniformMatrix4fv(this->pos_reference, 1, GL_TRUE, &mat.getRawData()[0]);
    glEnableVertexAttribArray ( 0 );
    
    glDrawArrays ( GL_TRIANGLES, 0, AssetManager::getMesh(this->mesh)->getSize());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    
}

void GameObject::rotate(const Vector3<float>& vec, float angle){
    this->quaternion = Quaternion<float>::rotate(quaternion, vec,angle);
}

void GameObject::loadMesh(std::string meshPath){
    this->mesh = AssetManager::loadMesh(meshPath);
   
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
