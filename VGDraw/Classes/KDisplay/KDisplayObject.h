#import <Foundation/Foundation.h>

/**
 * Base object used for display
 *
 * @author Jed Laudenslayer
 */
@interface KDisplayObject : NSObject
{
	BOOL skipRedraw_;
	
	float width_;
	float height_;
}

/**
 * The width of the display object.
 */
@property (nonatomic, assign) float width;

/**
 * The height of the display object.
 */
@property (nonatomic, assign) float height;

/**
 * Method called by the display manager to render this object.
 *
 * Should not be called directly.
 */
- (void)render;

@end
