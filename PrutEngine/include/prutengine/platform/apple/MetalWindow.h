#import "./AbstractWindow.h"
#import "../../Application.hpp"
#import "./AppDelegate.h"
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import "./MetalViewController.h"
@interface MetalWindow : AbstractWindow

@property (nonatomic,retain) MTKView* metalView;

@property (nonatomic, retain) MetalViewController* metalController;

-(id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag;

-(void) setupAppleMetal: (NSRect)contentRect;


@end