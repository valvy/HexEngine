#ifndef PRUTENGINE_MAC_APP_H
#define PRUTENGINE_MAC_APP_H
#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
#elif TARGET_OS_MAC
#import <Cocoa/Cocoa.h>
#import "../Application.hpp"
NSApplication* application;

@interface MacApp : NSWindow <NSApplicationDelegate>{
	PrutEngine::Application* appInstance;

}

@property (nonatomic, retain) NSOpenGLView* glView;

-(void) drawLoop:(NSTimer*) timer;

@end


#endif
#endif
#endif
