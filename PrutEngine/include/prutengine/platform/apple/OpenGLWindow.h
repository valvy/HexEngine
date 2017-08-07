#import "./AbstractWindow.h"
#import "../../Application.hpp"
#import "./AppDelegate.h"
#import <memory>

@interface OpenGLWindow : AbstractWindow{
    std::unique_ptr<PrutEngine::Platform::MacFriend> macFriend;
}

@property (nonatomic, retain) NSOpenGLView* glView;


-(void)setupOpenGL:(NSRect)contentRect;

-(id)initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag;

-(void) drawLoop:(NSTimer*)timer;

@end