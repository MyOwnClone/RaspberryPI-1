#import <Foundation/Foundation.h>
#import "KDisplayObject.h"

/**
 * Display Manager Class
 *
 * @author Jed Laudenslayer
 */
@interface KDisplayManager : NSObject
{
    KDisplayObject *rootObject_;
}

/**
 * Singleton Method
 */
+ (KDisplayManager *)sharedInstance;

/**
 * Method used to load and set a root display object.
 *
 * @param displayObject The object to use as the root of your display.
 */
- (void)loadRootDisplayObject:(KDisplayObject *)displayObject;

/**
 * Main display loop.
 */
- (void)loop;

@end
