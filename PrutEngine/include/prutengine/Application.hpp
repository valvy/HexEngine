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
		std::shared_ptr<AbstractScene> currentScene;
		/**
		* the instance of the application (it's a singleton)
		*/
		static std::shared_ptr<Application> instance;
		
		
		float time_per_frame;

	protected:
		/**
		* Loops the program
		*/
		void setInstance(Application* instance);
		void update();
	
		/**
		* private constructor so it enforces only on instance
		*/
		Application();
		void initialize();
	public:
		virtual void awake();
		void loadScene(std::shared_ptr<AbstractScene> scene);
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
		
		virtual void loop() = 0;
		/**
		* Cleans up the data and stops the program
		*/
		void quit();
	};
}


#endif
