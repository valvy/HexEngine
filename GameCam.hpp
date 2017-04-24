#ifndef GAME_CAM_HPP
#define GAME_CAM_HPP
#include "Camera.hpp"


class GameCam : public Camera{
private:
    float height;
protected:
    virtual void update(float tpf) override;
    virtual void onScroll(float velocityX, float velocityY) override;
public:
    GameCam(const Vector3<float>& position);
    
};



#endif