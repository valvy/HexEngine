#ifndef HEX_GAME_SCENE_HPP
#define HEX_GAME_SCENE_HPP
#include "AbstractScene.hpp"

enum class PlayerType { HUMAN, COMPUTER};

class HexGameScene : public AbstractScene{
public:
	HexGameScene();
protected:
    virtual void keyDown(unsigned short keycode) override;
	virtual void update(float tpf) override;


};



#endif
