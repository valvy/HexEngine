#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <memory>
#include "AbstractScene.hpp"
#include "Math/Vector2.hpp"
#include "Math/Vector4.hpp"
/**
* This class manages all the input of the Hex application.
* Starting point of the model view controller.
* @author Heiko van der Heijden
*/
class Application{
private:
	std::unique_ptr<AbstractScene> currentScene;
	/**
	* the instance of the application (it's a singleton)
	*/
	static std::shared_ptr<Application> instance;
    void start();
    
    float time_per_frame;
	/**
	* private constructor so it enforces only on instance
	*/
	Application();
public:
	/**
	* gets the instance of the application
	* if instance is null it creates a new instance
	*/
	static std::shared_ptr<Application> getInstance();
	/**
	* Get's the resource path 
	*/
	std::string getAppPath() const;
    
    Vector2<float> getMouseLocation() const;
    Vector4<float> getWindowSize() const;
    
    void onScroll(float velocityX, float velocityY);
    void keyDown(unsigned short keycode);
    
	/**
	* Loops the program
	*/
	void loop();	
	/**
	* Cleans up the data and stops the program
	*/
	void quit();
};

#endif
