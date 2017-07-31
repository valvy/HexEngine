#ifndef PRUTENGINE_GAMEOBJECT_HPP
#define PRUTENGINE_GAMEOBJECT_HPP
#include "./math/Vector3.hpp"
#include "./platform/OpenGL.hpp"
#include "./Application.hpp"
#include "./math/Quaternion.hpp"


namespace PrutEngine{
    class AbstractScene;

    class GameObject{
        friend AbstractScene;
    private:
        Math::Quaternion<float> quaternion;
        Math::Vector3<float> scale;
        Math::Vector3<float> position;
        std::shared_ptr<Data::Mesh> mesh;
        std::shared_ptr<Data::GLProgram> program;
        std::shared_ptr<Data::Texture> texture;
        GLint pos_reference;
        
    protected:
        virtual void update(float tpf);
        void loadMesh(std::string meshPath);
        void loadTexture(std::string texturePath);
        virtual void onKeyDown(unsigned short keycode);
        template<typename... Arguments>
        void loadProgram(Arguments... shaders){
            auto assetManager =  Application::getInstance()->getAssetManager();
            this->program = assetManager->loadProgram(shaders...);
            //AssetManager::loadProgram(shaders...);
            this->pos_reference = glGetUniformLocation(program->getProgram(), "mv_matrix");
        }
    public:
        GameObject();
        void rotate(const Math::Vector3<float>& vec, float angle);
        void translate(const Math::Vector3<float>& vec, float speed);
        void setPosition(const Math::Vector3<float> &position);
        void setScale(const Math::Vector3<float> &scale);
        void setQuaternion(const Math::Quaternion<float> &quat);
        Math::Quaternion<float> getQuaternion() const;
        Math::Vector3<float> getScale() const;
        Math::Vector3<float> getPosition() const;
        virtual ~GameObject();
        
        

    };
}


#endif
