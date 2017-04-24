#include "AbstractScene.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"
#include "Application.hpp"
AbstractScene::AbstractScene(){
    this->cam = std::shared_ptr<Camera>(new Camera(Vector3<float>(0,0,0)));
}


void AbstractScene::update(float tpf){
    this->cam->update(tpf);

	for(auto it : this->gameObjects){
        it->update(tpf);
	}
    

}

void AbstractScene::onScroll(float velocityX, float velocityY){
  
    this->cam->onScroll(velocityX,velocityY);
    for(auto it : this->gameObjects){
        it->onScroll(velocityX,velocityY);
    }
}

void AbstractScene::keyDown(unsigned short keycode){
    this->cam->onKeyDown(keycode);
    for(auto it : this->gameObjects){
        it->onKeyDown(keycode);
    }
    
    if(keycode == 5000){
        Vector3<float> camPos = this->getCamera()->getPosition();
        
        Vector2<float> mousepos = Application::getInstance()->getMouseLocation();
        Vector4<float> screen = Application::getInstance()->getWindowSize();
        //calculate the percentage of the x position
        float width = (screen.z - screen.x) / 100;
        float percX = 50 - (((screen.z - screen.x) - mousepos.x) / width);
        
        float x = (-camPos.x + (percX / 5));
        
        float height = (screen.w - screen.y) / 100;
        float percY = 50 - (((screen.w - screen.y) - mousepos.y) / height);
        float y = (-camPos.y + (percY / 5));
        const float size = 1.5f;
        for(auto it : this->gameObjects){
            Vector3<float> pos = it->getPosition();
            if(x > (pos.x - size) && x < (pos.x + size )){
                if(y > (pos.y - size) && y < ((pos.y + size))){
                    it->onClick();
                }
              
            }
        }
        
      
    }
    
}

void AbstractScene::setCamera(Camera* cam){
    this->cam.reset();
    this->cam = std::shared_ptr<Camera>(cam);
}

std::shared_ptr<Camera> AbstractScene::getCamera() const {
    return this->cam;
}

void AbstractScene::addGameObject(GameObject* obj){
    this->gameObjects.push_back(obj);
}

void AbstractScene::remGameObject(GameObject* obj){

}

AbstractScene::~AbstractScene(){
    //delete gameobjects
    for(auto it : this->gameObjects){
        delete it;
    }
    this->gameObjects.clear();
    
    //delete camera
    this->cam.reset();
}