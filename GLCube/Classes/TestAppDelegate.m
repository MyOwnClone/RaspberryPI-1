#import "TestAppDelegate.h"
#import <unistd.h>

@implementation TestAppDelegate

- (void)dealloc
{
    [openGLCube_ release];
    [super dealloc];
}

- (void)appDidFinishLaunching
{
    openGLCube_ = [[Cube alloc] init];
    [openGLCube_ start];    
}

- (void)appRunLoop
{
    [openGLCube_ loop];
    usleep(5*1000);
}

@end
