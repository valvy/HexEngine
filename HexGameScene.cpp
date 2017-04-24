#include "HexGameScene.hpp"
#include "testCube.hpp"
#include "Hex.hpp"
#include "GameCam.hpp"
#include "Application.hpp"
#include "Math/Utilities.hpp"
#include <iostream>
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/
HexGameScene::HexGameScene(){
    this->setCamera(new GameCam(Vector3<float>(0,0,9)));
    float offset = 0;
    
  //  this->addGameObject(new Hex(Vector3<float>(0,0,3)));
    //this->addGameObject(new TestCube(Vector3<float>(0,1,4)));
    this->addGameObject(new TestCube(Vector3<float>(0.4f,0,9)));

    this->addGameObject(new Hex(Vector3<float>(1,0,4)));
  
 
  
    // this->addGameObject(new Hex(Vector3<float>(0,0,-15)));
   
    //this->addGameObject(new Hex(Vector3<float>(10,0,-15)));
    /*
    for(int x = 0; x < 11; x++){
        for(int y = 0; y < 11; y++){
            this->addGameObject(new Hex(Vector3<float>((x * 3) -13,
                                                       (y * 3) -20 + offset,
                                                       -15)));
        }
        offset ++;
    }
    std::cout<<"Test\n";*/
  /*  for(int x = 0; x < 11; x++){
        for(int y = 0; y < 11; y++){
            this->addGameObject(new Hex(Vector3<float>((x * 2.5) -13,
                                                       (y * 2.5) -15.5f + offset,
                                                       -15)));
        }
        offset ++;
    }
*/
 
}

void HexGameScene::keyDown(unsigned short keycode){
    AbstractScene::keyDown(keycode);

   
}

void HexGameScene::update(float tpf){
	AbstractScene::update(tpf);//Updates the gameobjects
}
