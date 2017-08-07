#import "prutengine/platform/apple/AppDelegate.h"
#import "prutengine/Application.hpp"
#import <string>
#import "prutengine/platform/apple/MacApp.h"
#import "prutengine/AssetManager.hpp"
#import "prutengine/exceptions/PrutEngineException.hpp"
#import "prutengine/platform/Input.hpp"
#import "prutengine/platform/apple/OpenGLWindow.h"

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

@implementation AppDelegate

@synthesize window;

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
    window = [[OpenGLWindow alloc]initWithContentRect:NSMakeRect(0, 0, 600, 600) styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |  NSWindowStyleMaskMiniaturizable   backing:NSBackingStoreBuffered defer:YES];
    
}

- (void)applicationWillFinishLaunching:(NSNotification *)notification{
    [self setupAppleMenu];
    [self setupWindow];
}

- (void)applicationWillTerminate:(NSNotification *)aNotification{
    Application::getInstance()->quit();
    [window closeWindow];
    
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

void Application::quit(){
    assetManager->clear();
    currentScene.reset();
    std::exit(EXIT_SUCCESS);
}

Graphics_Engine Application::getCurrentGraphicsEngine() const {
    return Graphics_Engine::OpenGL;
}

//std::string Application::getAppPath() const{
//   return [[[NSBundle mainBundle]resourcePath]UTF8String];
//}

bool Application::canUseAppleMetal() const {
    //
    
    return false;
    NSOperatingSystemVersion version = [[NSProcessInfo processInfo] operatingSystemVersion];
    return (version.majorVersion >= 10 && version.minorVersion >= 12);
}


void Application::run(){
  @autoreleasepool{
        NSApplication* application = [NSApplication sharedApplication];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];	
        app = [[AppDelegate alloc]init]; 
        [application setDelegate:app];
        [application run];
  }

}