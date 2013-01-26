#import <Foundation/Foundation.h>
#import "OpenApp.h"
#import "TestAppDelegate.h"

int main (int argc, const char *argv[])
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    int retVal = OpenAppMain(argc, argv, nil, NSStringFromClass([TestAppDelegate class]));
    [pool release];
    return retVal;
}
