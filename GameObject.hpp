#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "Math/Vector3.hpp"
#include "OpenGL.hpp"
#include "AssetManager.hpp"
#include "Math/Quaternion.hpp"
class AbstractScene;

class GameObject{
    friend AbstractScene;
private:
    Quaternion<float> quaternion;
    Vector3<float> scale;
    Vector3<float> position;
    unsigned short mesh;
    unsigned short program;
    unsigned short texture;
    GLint pos_reference;
    
protected:
    virtual void onClick();
    virtual void update(float tpf);
    void loadMesh(std::string meshPath);
    void loadTexture(std::string texturePath);
    virtual void onKeyDown(unsigned short keycode);
    virtual void onScroll(float velocityX, float velocityY);
    template<typename... Arguments>
    void loadProgram(Arguments... shaders){
        this->program = AssetManager::loadProgram(shaders...);
        this->pos_reference = glGetUniformLocation(AssetManager::getProgram(program), "mv_matrix");
    }
public:
    GameObject();
    void rotate(const Vector3<float>& vec, float angle);
    void translate(const Vector3<float>& vec, float speed);
    void setPosition(const Vector3<float> &position);
    void setScale(const Vector3<float> &scale);
    void setQuaternion(const Quaternion<float> &quat);
    Quaternion<float> getQuaternion() const;
    Vector3<float> getScale() const;
    Vector3<float> getPosition() const;
    virtual ~GameObject();
    
    

};

#endif
