#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
#elif TARGET_OS_MAC
#import <string>
#import "prutengine/platform/MacApp.h"
#import "prutengine/AssetManager.hpp"
#import "prutengine/exceptions/PrutEngineException.hpp"
#import "prutengine/platform/Input.hpp"
#include <iostream>
using namespace PrutEngine;
using namespace PrutEngine::Math;

NSApplication* application;

@implementation MacApp

@synthesize glView;
@synthesize metalView;

@synthesize metalController;

BOOL shouldStop = NO;
Graphics_Engine currentEngine;

-(id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag{
	if(self = [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:flag]){
        appInstance = Application::getInstance();
        currentEngine = appInstance->setRenderer();
        [self setTitle:[[NSProcessInfo processInfo] processName]];
        [self setAcceptsMouseMovedEvents:YES];
        
        switch(currentEngine){
            case Graphics_Engine::AppleMetal:{
                [self setupAppleMetal: contentRect];
                break;
            }
            default:
            [self setupOpenGL: contentRect];
        }
        [self center];
        [self makeKeyAndOrderFront:self];
        [self setAcceptsMouseMovedEvents:YES];
        [self makeKeyWindow];
        [self setOpaque:YES];
        appInstance->awake();

	}
	return self;
}


-(void) setupAppleMetal: (NSRect)contentRect{
    std::cout <<"Setting up experimental Metal support\n";
    metalView = [[MTKView alloc] initWithFrame:contentRect device:MTLCreateSystemDefaultDevice()];

    metalController = [[MetalViewController alloc] init];;
    [metalView setClearColor:MTLClearColorMake(0, 0, 0, 1)];
    [metalView setColorPixelFormat:MTLPixelFormatBGRA8Unorm];
    [metalView setDepthStencilPixelFormat:MTLPixelFormatDepth32Float];
    [metalController setView:self.metalView];
    [metalView setDelegate:metalController];
    
    
    [self setContentView:metalView];

    [metalController viewDidLoad];
}

-(void) setupOpenGL:(NSRect)contentRect {
       //Setup an opengl window with opengl 3_2+
        NSOpenGLPixelFormatAttribute pixelFormatAttributes[] ={
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
                NSOpenGLPFAColorSize    , 24                           ,
                NSOpenGLPFAAlphaSize    , 8                            ,
                NSOpenGLPFADoubleBuffer ,
                NSOpenGLPFAAccelerated  ,
                NSOpenGLPFANoRecovery   ,
                NSOpenGLPFADepthSize, (NSOpenGLPixelFormatAttribute)16
        };
	
        NSOpenGLPixelFormat* format = [[NSOpenGLPixelFormat alloc]initWithAttributes:pixelFormatAttributes];
        
        glView = [[NSOpenGLView alloc]initWithFrame:contentRect pixelFormat:format];
        
        //Set context and attach it to the window
        [[glView openGLContext]makeCurrentContext];
      
        //Do stuff required to make a fullscreen window
        [self setContentView:glView];
        [glView prepareOpenGL];

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CW);
    
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
}

-(void) drawLoop:(NSTimer*) timer{
    try{
        if(shouldStop){
            [self close];
            return;
        }
        if([self isVisible]){
            
            appInstance->loop();
            if(currentEngine == Graphics_Engine::OpenGL){
                [glView update];
                [[glView openGLContext] flushBuffer];
            } else if (currentEngine == Graphics_Engine::AppleMetal){
                [metalView draw];
            }

        }
    } catch(const PrutEngine::Exceptions::PrutEngineException exception){
        appInstance->quit();

    }

}

-(BOOL)canBecomeKeyWindow {
    //this is required to receive input..
    return YES;
}

-(void)keyDown:(NSEvent*) event{
    if(!shouldStop){
        appInstance->keyDown([event keyCode]);
    }
}


- (void)applicationWillFinishLaunching:(NSNotification *)notification{
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

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
	    [NSTimer scheduledTimerWithTimeInterval:0.000001 target:self selector:@selector(drawLoop:) userInfo:nil repeats:YES];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication{
	return YES;
}

- (void)applicationWillTerminate:(NSNotification *)aNotification{
    appInstance->quit();
    [self release]; //Object suicide.. it's no longer needed
}


-(void) dealloc{
    
	if(glView != nil){
		[glView clearGLContext];
		[glView release];
		glView = nil;
	}
	[super dealloc];
}

@end


MacApp* app;


Vector<float, 4> Application::getWindowSize() const{
    NSSize s = [app frame].size;
    NSPoint p = [app frame].origin;
    return Vector<float, 4>(p.x, p.y, s.width,s.height);
}

void Application::quit(){
    auto assetManager =  Application::getInstance()->getAssetManager();
    assetManager->clear();
    currentScene.reset();
    shouldStop = YES;
}

Graphics_Engine Application::getCurrentGraphicsEngine() const {
    return currentEngine;
}

std::string Application::getAppPath() const{
   return [[[NSBundle mainBundle]resourcePath]UTF8String];
}

bool Application::canUseAppleMetal() const {
    //return false;
    NSOperatingSystemVersion version = [[NSProcessInfo processInfo] operatingSystemVersion];
    return (version.majorVersion >= 10 && version.minorVersion >= 12);
}

void Application::run(){
    @autoreleasepool{
        application = [NSApplication sharedApplication];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];	
        app = [[MacApp alloc] initWithContentRect:NSMakeRect(0, 0, 600, 600) styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |  NSWindowStyleMaskMiniaturizable   backing:NSBackingStoreBuffered defer:YES];	
        [application setDelegate:app];
        [application run];
    }
}



/*
int main(int argc, char** argv){

}*/
#endif
#endif
