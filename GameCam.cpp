#include "GameCam.hpp"
#include <iostream>
#include "Application.hpp"
GameCam::GameCam(const Vector3<float>& position) : Camera(position){
 
}

void GameCam::update(float tpf){
    Camera::update(tpf);

    /*
    Vector2<float> mousepos = Application::getInstance()->getMouseLocation();
    Vector4<float> screen = Application::getInstance()->getWindowSize();
    mousepos.x -= screen.x; //Keep in the window
    mousepos.y -= screen.y;
    
    //Only do it when the mouse is inside the screen
    if(!(mousepos.x >= screen.z) && !(mousepos.y >= screen.w) && mousepos.y >= 0 && mousepos.x >= 0){
        //Half the speed so it will actually go up (zero is on bottom)
        
        float speedX = -(mousepos.x - (screen.z / 2));
        float speedY = -(mousepos.y - (screen.w / 2));
        
        if(speedX < 200 && speedX > -200){
            speedX = 0;
        }
        if(speedY < 200 && speedY > -200) {
            speedY = 0;
        }
        
        //Never to far from the center
        if((this->getPosition().x > 10 && speedX > 0) || (this->getPosition().x < -10 && speedX < 0)){
            speedX = 0;
        }
        
        if((this->getPosition().y > 10 && speedY > 0) || (this->getPosition().y < -12 && speedY < 0)){
            speedY = 0;
        }
           
        this->translate(Vector3<float>(speedX,speedY,
                                       0), 0.03f * tpf);
    }*/
}

void GameCam::onScroll(float velocityX, float velocityY){
   // this->translate(Vector3<float>(0,0,1),velocityY);
   /* if(this->getPosition().z < - 30){
        //No lower then 30
        this->setPosition(Vector3<float>(
                          this->getPosition().x,
                          this->getPosition().y,
                           -30
                                         ));
    }else if(this->getPosition().z > 6){
        //No higher then 6
        this->setPosition(Vector3<float>(
                                         this->getPosition().x,
                                         this->getPosition().y,
                                         6
                                         ));
        
    }*/
}
