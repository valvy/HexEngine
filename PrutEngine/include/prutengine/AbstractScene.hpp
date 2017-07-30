#ifndef PRUTENGINE_ABSTRACT_SCENE_HPP
#define PRUTENGINE_ABSTRACT_SCENE_HPP
#include <vector>
#include <memory>

namespace PrutEngine{
    class GameObject;
    class Application;
    class Camera;

    class AbstractScene{
    friend Application;	
    private:
        std::shared_ptr<Camera> cam;
        std::vector<GameObject*> gameObjects;
        
    protected:
        virtual void update(float tpf);
        virtual void keyDown(unsigned short keycode);
        void addGameObject(GameObject* obj);
        void removeGameObject(GameObject* obj);
        void setCamera(Camera* cam);
    public:
        AbstractScene();
        std::shared_ptr<Camera> getCamera() const;
        ~AbstractScene();
	
    };	
}



#endif
