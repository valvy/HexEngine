#ifndef MAC_APP_H
#define MAC_APP_H
#ifdef __APPLE__
#import <Cocoa/Cocoa.h>
#import "Application.hpp"
NSApplication* application;

@interface MacApp : NSWindow <NSApplicationDelegate>{
	std::shared_ptr<Application> appInstance;

}

@property (nonatomic, retain) NSOpenGLView* glView;

-(void) drawLoop:(NSTimer*) timer;

@end

#endif
#endif
