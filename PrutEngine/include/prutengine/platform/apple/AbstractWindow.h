#import <Cocoa/Cocoa.h>


@interface AbstractWindow : NSWindow{
    BOOL shouldStop;
    
}



-(void) closeWindow;

-(BOOL) getShouldStop;

@end