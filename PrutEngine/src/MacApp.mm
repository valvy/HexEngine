#ifdef __APPLE__
#import <string>
#import "prutengine/platform/MacApp.h"
#import "prutengine/AssetManager.hpp"
#import "prutengine/exceptions/PrutEngineException.hpp"
#import "prutengine/platform/Input.hpp"

using namespace PrutEngine;
using namespace PrutEngine::Math;

@implementation MacApp

@synthesize glView;

BOOL shouldStop = NO;

-(id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag{
	if(self = [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:flag]){
        [self setTitle:[[NSProcessInfo processInfo] processName]];
        [self setAcceptsMouseMovedEvents:YES];
        
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
        [self makeKeyAndOrderFront:self];
        [self setAcceptsMouseMovedEvents:YES];
        [self makeKeyWindow];
        [self setOpaque:YES];
         glEnable(GL_CULL_FACE);
        glFrontFace(GL_CW);
    
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    
        appInstance = Application::getInstance();
        appInstance->awake();

	}
	return self;
}

-(void) drawLoop:(NSTimer*) timer{
    try{
        if(shouldStop){
            [self close];
            return;
        }
        if([self isVisible]){
            
            appInstance->loop();
            [glView update];
            [[glView openGLContext] flushBuffer];
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


Vector4<float> Application::getWindowSize() const{
    NSSize s = [app frame].size;
    NSPoint p = [app frame].origin;
    return Vector4<float>(p.x, p.y, s.width,s.height);
}

void Application::quit(){
    shouldStop = YES;
    AssetManager::clear();
    instance.reset();
}

std::string Application::getAppPath() const{
   return [[[NSBundle mainBundle]resourcePath]UTF8String];
}


void Application::initialize(){
	application = [NSApplication sharedApplication];
   	[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];	
	app = [[MacApp alloc] initWithContentRect:NSMakeRect(0, 0, 600, 600) styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |  NSWindowStyleMaskMiniaturizable   backing:NSBackingStoreBuffered defer:YES];	
	[application setDelegate:app];
	[application run];
}



/*
int main(int argc, char** argv){

}*/
#endif
