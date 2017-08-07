#import <Cocoa/Cocoa.h>
#import "./AbstractWindow.h"


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
        };
    }
}


@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (nonatomic,retain) AbstractWindow* window;

- (void)setupAppleMenu;

-(NSRect) getWindowSize;

- (void) setupWindow;

@end
