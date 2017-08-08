#import "prutengine/platform/apple/OpenGLWindow.h"
#import "prutengine/exceptions/PrutEngineException.hpp"
#import <cstdlib>

@implementation OpenGLWindow

@synthesize glView;

-(id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag{
    if(self = [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:flag]){
        macFriend = std::unique_ptr<PrutEngine::Platform::MacFriend>(new PrutEngine::Platform::MacFriend());
        [self setTitle:[[NSProcessInfo processInfo] processName]];
        [self setAcceptsMouseMovedEvents:YES];
        [self setupOpenGL: contentRect];
        macFriend->awake();
        [self center];
        [self makeKeyAndOrderFront:self];
        [self setAcceptsMouseMovedEvents:YES];
        [self makeKeyWindow];
        [self setOpaque:YES];
        [NSTimer scheduledTimerWithTimeInterval:0.000001 target:self selector:@selector(drawLoop:) userInfo:nil repeats:YES];

    }
    return self;
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

-(BOOL)canBecomeKeyWindow {
    return YES;
}

-(void) drawLoop:(NSTimer*) timer{
  try{
        if(macFriend->shouldStop()){
            [glView clearGLContext];
            [timer invalidate];
            [self close];
            return;
        }
        else if([self isVisible]){
            macFriend->loop();
            [glView update];
            [[glView openGLContext] flushBuffer];

        }
    } catch(const PrutEngine::Exceptions::PrutEngineException exception){
        PrutEngine::Application::getInstance()->quit();
        [glView clearGLContext];
        [timer invalidate];
        [self close];
        std::exit(EXIT_FAILURE);
    }
}

-(void)keyDown:(NSEvent*) event{
    if(!macFriend->shouldStop()){
        macFriend->keyDown([event keyCode]);
    }
}


@end