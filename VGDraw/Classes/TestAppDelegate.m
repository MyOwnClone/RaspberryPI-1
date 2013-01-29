#import "TestAppDelegate.h"
#import <unistd.h>
#import "KDisplayManager.h"
#import "AppRootView.h"

@implementation TestAppDelegate

- (void)appDidFinishLaunching
{
    AppRootView *rootView = [[AppRootView alloc] init];
    [[KDisplayManager sharedInstance] loadRootDisplayObject:rootView];
    [rootView release];
}

- (void)appRunLoop
{
    [[KDisplayManager sharedInstance] loop];
}

@end
