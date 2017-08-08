#import "prutengine/platform/apple/MetalWindow.h"
#import "prutengine/exceptions/PrutEngineException.hpp"
#import <cstdlib>

@implementation MetalWindow

@synthesize metalView;

@synthesize metalController;

-(id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag{
    if(self = [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:flag]){
        [self setTitle:[[NSProcessInfo processInfo] processName]];
        [self setAcceptsMouseMovedEvents:YES];
        [self setupAppleMetal:contentRect];
        [self center];
        [self makeKeyAndOrderFront:self];
        [self setAcceptsMouseMovedEvents:YES];
        [self makeKeyWindow];
        [self setOpaque:YES];
    }
    return self;

}

-(void) setupAppleMetal: (NSRect)contentRect{
    NSLog(@"Setting up experimental Metal support\n");
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

@end