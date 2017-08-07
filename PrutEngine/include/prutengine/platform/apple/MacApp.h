/*#ifndef PRUTENGINE_MAC_APP_H
#define PRUTENGINE_MAC_APP_H
#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
#elif TARGET_OS_MAC
#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#import "./MetalViewController.h"

#import "../../Application.hpp"


@interface MacApp : NSWindow <NSApplicationDelegate>{
	PrutEngine::Application* appInstance;
}

@property (nonatomic, retain) NSOpenGLView* glView;

@property (nonatomic,retain) MTKView* metalView;

@property (nonatomic, retain) MetalViewController* metalController;

-(void) setupAppleMetal: (NSRect)contentRect ;
-(void) setupOpenGL: (NSRect)contentRect ;
-(void) drawLoop:(NSTimer*) timer;

@end


#endif
#endif
#endif
*/