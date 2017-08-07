
#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import "./MetalRenderer.h"

@interface MetalViewController : NSViewController<MTKViewDelegate, RenderDestinationProvider>

@end


