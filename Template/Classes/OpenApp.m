#import "OpenApp.h"

@implementation OpenApp

@synthesize delegate = delegate_;

- (void)ready
{
    if (self.delegate != nil)
    {
        [self.delegate appDidFinishLaunching];
    }    
}

@end

int OpenAppMain(int argc, const char *argv[], NSString *principalClassName, NSString *delegateClassName)
{
    OpenApp *app = [[[OpenApp alloc] init] autorelease];
    id <OpenAppDelegate> delegate = [[NSClassFromString(delegateClassName) alloc] init];
    
    app.delegate = delegate;    
    [delegate release];
    [app ready];
    
    while (YES) 
    { 
        [app.delegate appRunLoop];
    }

    return 0;
}
