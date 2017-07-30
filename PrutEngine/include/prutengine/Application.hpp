#ifndef PRUTENGINE_APPLICATION_HPP
#define PRUTENGINE_APPLICATION_HPP
#include <memory>
#include "./AbstractScene.hpp"
#include "./math/Vector2.hpp"
#include "./math/Vector4.hpp"

namespace PrutEngine{
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
		
		Math::Vector4<float> getWindowSize() const;
		
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
}


#endif
