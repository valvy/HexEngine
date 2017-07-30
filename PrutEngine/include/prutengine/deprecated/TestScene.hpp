#ifndef PRUTENGINE_TEST_SCENE_HPP
#define PRUTENGINE_TEST_SCENE_HPP
#include "../AbstractScene.hpp"

namespace PrutEngine{

	
	class TestScene : public AbstractScene{
	public:
	[[deprecated("Should be moved to unit tests")]]
		TestScene();
	protected:
		virtual void keyDown(unsigned short keycode) override;
		virtual void update(float tpf) override;


	};

}

#endif
