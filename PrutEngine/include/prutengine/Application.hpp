#ifndef PRUTENGINE_APPLICATION_HPP
#define PRUTENGINE_APPLICATION_HPP
#include <memory>
#include "./AbstractScene.hpp"
#include "./math/Vector.hpp"
#include "./GraphicsController.hpp"
#include "prutengine/AssetManager.hpp"
#include <ostream>
namespace PrutEngine{



	#ifdef __APPLE__
	namespace Platform{
		class MacFriend;
	}
	#elif __linux__
	namespace Platform{
		namespace GnuLinux{

			class GnuXApp;
		}
	}
	#endif
	

	/**
	* This class manages all the input of the Hex application.
	* Starting point of the model view controller.
	* @author Heiko van der Heijden
	*/
	class Application{
		#ifdef __APPLE__
		friend Platform::MacFriend;
		#elif __linux__
		friend Platform::GnuLinux::GnuXApp;
		#endif
	private:
		std::shared_ptr<AbstractScene> currentScene;
		/**
		* the instance of the application (it's a singleton)
		*/
		bool shouldStop = false;
		static Application* instance;
		std::shared_ptr<AssetManager> assetManager;
		std::shared_ptr<GraphicsController> graphicsController;
		float time_per_frame;
		void keyDown(unsigned short keycode);
		void clean();
	protected:
		/**
		* Loops the program
		*/
		void setInstance(Application* instance);
		void update();
		
		bool canUseAppleMetal() const ;
		
		
		virtual void loop() = 0;
		/**
		* private constructor so it enforces only on instance
		*/
		Application();
        virtual Graphics_Engine setRenderer() = 0;
		void run();
		virtual void awake();
	public:
		virtual ~Application();
		std::shared_ptr<AssetManager> getAssetManager();
	
		void setWindowTitle(const std::string& title);

		void loadScene(std::shared_ptr<AbstractScene> scene);
		/**
		* gets the instance of the application
		* if instance is null it creates a new instance
		*/
		static Application* getInstance();
		
		std::shared_ptr<GraphicsController> getGraphicsController() const ;
		Math::Vector4f getWindowSize() const;
		
		/**
		* Cleans up the data and stops the program
		*/
		void quit();
	};
}


#endif
