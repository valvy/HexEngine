#ifndef PRUTENGINE_ABSTRACT_SCENE_HPP
#define PRUTENGINE_ABSTRACT_SCENE_HPP

#include <vector>
#include <memory>

namespace PrutEngine{
    class Node;
    class Application;
    class Camera;

    class AbstractScene{
    friend Application;	
    private:
        std::shared_ptr<Camera> cam;
        std::vector<std::shared_ptr<Node>> gameObjects;
        
    protected:
        virtual void awake();
        virtual void update(const float& tpf);
        virtual void keyDown(const unsigned short& keycode);
        void addGameObject(std::shared_ptr<Node> obj);
        void removeGameObject(std::shared_ptr<Node> obj);
        void setCamera(std::shared_ptr<Camera> cam);
    public:
        AbstractScene();
        std::shared_ptr<Camera> getCamera() const;
        ~AbstractScene();
	
    };	
}



#endif
