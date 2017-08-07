#import "prutengine/platform/apple/AbstractWindow.h"

@implementation AbstractWindow


-(void) closeWindow{
    shouldStop = YES;
}

-(BOOL) getShouldStop{
    return shouldStop;
}
@end
