#import <Foundation/Foundation.h>

@protocol OpenAppDelegate <NSObject>

@required

/**
 * Called when the application is done launching.
 */
- (void)appDidFinishLaunching;

/**
 * Method used to keep the application running.
 */
- (void)appRunLoop;

@end

/**
 * Base class for creating an Objective C application.
 *
 * @author Jed Laudenslayer
 */
@interface OpenApp : NSObject
{
    id <OpenAppDelegate> delegate_;
}

/**
 * Delegate that will respond to the application launch.
 */
@property (nonatomic, retain) id<OpenAppDelegate> delegate; 

/**
 * Called when the application has finished launching.
 */
- (void)ready;

@end

int OpenAppMain(int argc, const char *argv[], NSString *principalClassName, NSString *delegateClassName);
