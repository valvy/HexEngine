#include "prutengine/GameObject.hpp"
#include "prutengine/math/Utilities.hpp"
#include "prutengine/math/Matrix.hpp"
#include "prutengine/exceptions/AssetNotLoadedException.hpp"
#include <iostream>
using namespace PrutEngine;
using namespace PrutEngine::Math;

GameObject::GameObject(){
    this->setScale(Vector<float,3>(1,1,1));
}

GameObject::~GameObject(){

}



std::shared_ptr<Renderer> GameObject::getRenderer() const{
    return this->renderer;
}

void GameObject::translate(const Vector<float,3>& vec, float speed){
    this->position.setX(this->position.getX() + vec.getX() * speed);
    this->position.setY(this->position.getY() + vec.getY() * speed);
    this->position.setZ(this->position.getZ() + vec.getZ() * speed);
}

void GameObject::onKeyDown(unsigned short keyCode){
    //virtual
}

void GameObject::setRenderer(std::shared_ptr<Renderer> renderer){
    this->renderer = renderer;
}

void GameObject::update(float tpf){
   
    using namespace PrutEngine::Exceptions;
    auto assetManager =  Application::getInstance()->getAssetManager(); 
    const Graphics_Engine engine = Application::getInstance()->getGraphicsController()->getCurrentGraphicsEngine();
    if(engine == Graphics_Engine::AppleMetal){
        return;
    }
    
    Data::GraphicsProgram* program = this->getRenderer()->getProgram().get();
    Data::Mesh* mesh = this->getRenderer()->getMesh().get();
    Data::Texture* texture = this->getRenderer()->getTexture().get();

    //AssertAssetNotLoaded(this->texture == nullptr, "No texture was loaded..");
//    AssertAssetNotLoaded(this->mesh == nullptr, "No mesh was loaded");
  //  AssertAssetNotLoaded(this->program == nullptr, "No program was compiled");

    Data::GLProgram* tmpProgram = static_cast<Data::GLProgram*>(program);
    GLint pos_reference = glGetUniformLocation(tmpProgram->getProgram(), "mv_matrix");
    //setup the program and mesh
    glUseProgram(tmpProgram->getProgram());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture->getTexture());
    glBindVertexArray(mesh->getVao());
    
    //Make the calculation
    Matrix4x4<float> mat = Matrix4x4<float>::identityMatrix();
    mat = Matrix4x4<float>::scale(mat,this->scale);
    Matrix4x4<float> pos = Matrix4x4<GLfloat>::translate(Matrix4x4<float>::identityMatrix(),position);
    
    mat = Matrix4x4<float>::multiply(mat,pos);
    mat = Matrix4x4<float>::multiply(mat, Quaternion<float>::quaternionToMatrix(this->quaternion));
    
    //pass it to opengl
    glUniformMatrix4fv(pos_reference, 1, GL_TRUE, &mat.getRawData()[0]);
    glEnableVertexAttribArray ( 0 );
    
    glDrawArrays ( GL_TRIANGLES, 0, mesh->getSize());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    
}

void GameObject::rotate(const Vector<float,3>& vec, float angle){
    this->quaternion = Quaternion<float>::rotate(quaternion, vec,angle);
}


Quaternion<float> GameObject::getQuaternion() const{
    return this->quaternion;
}

Vector<float,3> GameObject::getScale() const{
    return this->scale;
}

Vector<float,3> GameObject::getPosition() const{
    return this->position;
}

void GameObject::setPosition(const Vector<float,3> &position){
    this->position = position;
}

void GameObject::setScale(const Vector<float,3> &scale){
    this->scale = scale;
}

void GameObject::setQuaternion(const Quaternion<float> &quat){
    this->quaternion = quat;
}
