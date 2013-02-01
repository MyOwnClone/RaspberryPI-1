#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>

/**
 * Display Manager Class
 *
 * @author Jed Laudenslayer
 */
@interface KDisplayManager : NSObject
{
    CALayer *rootLayer_;
}

/**
 * Singleton Method
 */
+ (KDisplayManager *)sharedInstance;

/**
 * Method used to load and set a root display object.
 *
 * @param layer The layer to use as the root of your display.
 */
- (void)loadRootLayer:(CALayer *)layer;

/**
 * Main display loop.
 */
- (void)loop;

@end
