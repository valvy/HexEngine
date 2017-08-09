#import <Cocoa/Cocoa.h>
#import "./AbstractWindow.h"
#import "../../GraphicsController.hpp"

namespace PrutEngine{
    class Application;
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
            void disableLoadShader();
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
