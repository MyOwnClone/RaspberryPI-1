#import <Foundation/Foundation.h>

#include "VG/openvg.h"
#include "VG/vgu.h"

/**
 * Base object used for display
 *
 * @author Jed Laudenslayer
 */
@interface KDisplayObject : NSObject
{
	VGfloat width_;
	VGfloat height_;
}

/**
 * The width of the display object.
 */
@property (nonatomic, assign) VGfloat width;

/**
 * The height of the display object.
 */
@property (nonatomic, assign) VGfloat height;

/**
 * Method called by the display manager to render this object.
 *
 * Should not be called directly.
 */
- (void)render;

@end
