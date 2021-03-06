#import <Cocoa/Cocoa.h>
#import "./AbstractWindow.h"
#import "../../GraphicsController.hpp"
#import <functional>
namespace PrutEngine{
    class Application;
    class Renderer;
    
    namespace Platform{
        class MacFriend{
            private:
            Application* application;
            public:
            MacFriend();
            void loop();
            void awake();
            void keyDown(unsigned short keydown);
            bool shouldStop() const;
            void setLoadShader(std::function<void(std::string path, Shader_Types type, Data::Shader* shader)> loadShader);
            void setCompileProgram(std::function<Data::GraphicsProgram*(const std::string& name, const std::vector<std::shared_ptr<Data::Shader>>& shaders)> compileProgram);
            void setCreateRenderer(std::function<std::shared_ptr<Renderer>(const std::string&, const std::string&, std::shared_ptr<Data::GraphicsProgram>)> createRendererFunction);
            void setDrawFunction(std::function<void(const std::shared_ptr<Renderer>&, const std::shared_ptr<Transform>&)> drawFunction);
        };
    }
}


@interface AppDelegate : NSObject <NSApplicationDelegate>{
    PrutEngine::Graphics_Engine engine;
}

@property (nonatomic,retain) AbstractWindow* window;

- (id) initWithRenderer:(PrutEngine::Graphics_Engine) engine;

- (void)setupAppleMenu;

-(NSRect) getWindowSize;

- (void) setupWindow;

@end
