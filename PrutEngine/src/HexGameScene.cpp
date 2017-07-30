#include "HexGameScene.hpp"
#include "testCube.hpp"
#include "Hex.hpp"
#include "GameCam.hpp"
#include "Application.hpp"
#include "Math/Utilities.hpp"
#include <iostream>
HexGameScene::HexGameScene(){
    this->setCamera(new GameCam(Vector3<float>(0,0,9)));
    float offset = 0;
    
    for(int x = 0; x < 11; x++){
        for(int y = 0; y < 11; y++){
            this->addGameObject(new Hex(Vector3<float>((x * 2.1f) -13,
                                                       (y * 2.1f) -20 + offset,
                                                       3)));
        }
        offset ++;
    }

 
}

void HexGameScene::keyDown(unsigned short keycode){
    AbstractScene::keyDown(keycode);

   
}

void HexGameScene::update(float tpf){
	AbstractScene::update(tpf);//Updates the gameobjects
}
