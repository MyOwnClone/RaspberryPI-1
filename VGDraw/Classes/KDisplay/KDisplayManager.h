#import <Foundation/Foundation.h>

/**
 * Display Manager Class
 *
 * @author Jed Laudenslayer
 */
@interface KDisplayManager : NSObject

/**
 *
 */
+ (KDisplayManager *)sharedInstance;

/**
 * Method used to startup the display.
 */
- (void)startUp;

/**
 * Method used to shut down the display.
 */
- (void)shutDown;

@end
