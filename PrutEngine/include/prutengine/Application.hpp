#ifndef PRUTENGINE_APPLICATION_HPP
#define PRUTENGINE_APPLICATION_HPP
#include <memory>
#include "./AbstractScene.hpp"
#include "./math/Vector.hpp"
#include "./GraphicsController.hpp"
#include "prutengine/AssetManager.hpp"
#include <ostream>
namespace PrutEngine{

	enum class Graphics_Engine{
		OpenGL = 0,
		AppleMetal

		
	} ;

/*
	std::ostream& operator<<(std::ostream& out, const Graphics_Engine value){
		switch(value){
			case Graphics_Engine::AppleMetal:
			out << std::string("Apple Metal");
			break;
			default:
			out << std::string("OpenGL");
			break;
		}
		return out;
	}*/

	//std::ostream& operator<<(std::ostream& out, const Graphics_Engine value)

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
		static Application* instance;
		std::shared_ptr<AssetManager> assetManager;
		std::shared_ptr<GraphicsController> graphicsController;
		float time_per_frame;

	protected:
		/**
		* Loops the program
		*/
		void setInstance(Application* instance);
		void update();
		bool canUseAppleMetal() const ;
		
	
		/**
		* private constructor so it enforces only on instance
		*/
		Application();
		void run();
	public:
		virtual Graphics_Engine setRenderer() = 0;

		virtual ~Application();
		std::shared_ptr<AssetManager> getAssetManager();
		virtual void awake();
		void loadScene(std::shared_ptr<AbstractScene> scene);
		/**
		* gets the instance of the application
		* if instance is null it creates a new instance
		*/
		static Application* getInstance();
		/**
		* Get's the resource path 
		*/
		std::string getAppPath() const;
		Graphics_Engine getCurrentGraphicsEngine() const;
		
		std::shared_ptr<GraphicsController> getGraphicsController() const;
		Math::Vector<float, 4> getWindowSize() const;
		
		void keyDown(unsigned short keycode);
		
		virtual void loop() = 0;
		/**
		* Cleans up the data and stops the program
		*/
		void quit();
	};
}


#endif
