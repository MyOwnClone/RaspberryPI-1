#import "TestAppDelegate.h"
#import <unistd.h>

@implementation TestAppDelegate

- (void)dealloc
{
    [super dealloc];
}

- (void)appDidFinishLaunching
{
    NSLog(@"appDidFinishLaunching");    
}

- (void)appRunLoop
{
    usleep(5*1000);
}

@end
