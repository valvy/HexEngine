#import "prutengine/platform/apple/AppDelegate.h"
#import "prutengine/Application.hpp"
#import <string>
#import "prutengine/platform/apple/MacApp.h"
#import "prutengine/AssetManager.hpp"
#import "prutengine/exceptions/PrutEngineException.hpp"
#import "prutengine/platform/Input.hpp"
#import "prutengine/platform/apple/OpenGLWindow.h"
#import "prutengine/platform/apple/MetalWindow.h"

using namespace PrutEngine;
using namespace PrutEngine::Math;

Platform::MacFriend::MacFriend(){
    this->application = Application::getInstance();
}

void Platform::MacFriend::loop(){
    this->application->loop();
}

void Platform::MacFriend::awake(){
    this->application->awake();
}


void Platform::MacFriend::keyDown(unsigned short keydown){
    this->application->keyDown(keydown);
}

bool Platform::MacFriend::shouldStop() const{
    return this->application->shouldStop;
}

@implementation AppDelegate

@synthesize window;

- (id) initWithRenderer:(Graphics_Engine) graphics_engine {
    if(self = [super init]){
        engine = graphics_engine;
    }
    return self;
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication{
    return YES;
}


- (void)setupAppleMenu{
    //setup the menubar
    NSMenu* mainMenu = [[NSMenu alloc] initWithTitle:@"MainMenu"];
    NSMenuItem* appleMenuItem;
    NSMenu* appleSubMenu;
    NSString* applicationName = [[NSProcessInfo processInfo]processName];
    NSMenuItem* appMenuItem;
    
    appleMenuItem = [mainMenu addItemWithTitle:@"Apple" action:NULL keyEquivalent:@""];
    appleSubMenu = [[NSMenu alloc]initWithTitle:@"Apple"];
    
    appMenuItem = [appleSubMenu addItemWithTitle:[NSString stringWithFormat:@"%@ %@", NSLocalizedString(@"About", nil), applicationName] action:@selector(orderFrontStandardAboutPanel:) keyEquivalent:@""];
    [appMenuItem setTarget:NSApp];
    [appleSubMenu addItem:[NSMenuItem separatorItem]];
    
    appMenuItem = [appleSubMenu addItemWithTitle:[NSString stringWithFormat:@"%@ %@", NSLocalizedString(@"Quit", nil), applicationName] action:@selector(terminate:) keyEquivalent:@"q"];
    [appMenuItem setTarget:NSApp];
    
    [mainMenu setSubmenu:appleSubMenu forItem:appleMenuItem];
    [NSApp setMainMenu:mainMenu];
}

- (void) setupWindow{
    if(engine == Graphics_Engine::OpenGL){
        window = [[OpenGLWindow alloc]initWithContentRect:NSMakeRect(0, 0, 600, 600) styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |  NSWindowStyleMaskMiniaturizable   backing:NSBackingStoreBuffered defer:YES];
    } else if(engine == Graphics_Engine::AppleMetal){
        window = [[MetalWindow alloc]initWithContentRect:NSMakeRect(0, 0, 600, 600) styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |  NSWindowStyleMaskMiniaturizable   backing:NSBackingStoreBuffered defer:YES];
    }
}

- (void)applicationWillFinishLaunching:(NSNotification *)notification{
    [self setupAppleMenu];
    [self setupWindow];
}

- (void)applicationWillTerminate:(NSNotification *)aNotification{
    Application::getInstance()->quit();
}

- (NSRect) getWindowSize{
    return [window frame];
}

@end

AppDelegate* app;

Vector4f Application::getWindowSize() const{
    NSSize s = [app getWindowSize].size;
    NSPoint p = [app getWindowSize].origin;
    return Vector4f(p.x, p.y, s.width,s.height);
}


bool Application::canUseAppleMetal() const {
    NSOperatingSystemVersion version = [[NSProcessInfo processInfo] operatingSystemVersion];
    return (version.majorVersion >= 10 && version.minorVersion >= 12);
}


void Application::run(){
    this->graphicsController = std::shared_ptr<GraphicsController>(new GraphicsController(this->setRenderer()));
    @autoreleasepool{
      
      NSApplication* application = [NSApplication sharedApplication];
      [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
      app = [[AppDelegate alloc]init];
      [application setDelegate:app];
      [application run];
  }

}
