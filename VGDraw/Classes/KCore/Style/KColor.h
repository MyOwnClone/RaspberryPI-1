#import <Foundation/Foundation.h>

#include "VG/openvg.h"
#include "VG/vgu.h"

/**
 * KColor for simplifying color creation.
 *
 * @author Jed Laudenslayer
 */
@interface KColor : NSObject
{
    VGfloat red_;
    VGfloat green_;
    VGfloat blue_;
    VGfloat alpha_;
}

/**
 * The red value for this color.
 */
@property (nonatomic, assign) VGfloat red;

/**
 * The green value for this color.
 */
@property (nonatomic, assign) VGfloat green;

/**
 * The blue value for this color.
 */
@property (nonatomic, assign) VGfloat blue;

/**
 * The alpha value for this color.
 */
@property (nonatomic, assign) VGfloat alpha;

/**
 * Create a color with specific red/green/blue values.
 *
 * @param red Red value for the color.
 * @param green Green value for the color.
 * @param blue Blue value for the color.
 * @param alpha The alpha value for the color.
 * @return The color object created.
 */
- (KColor *)initWithDeviceRed:(VGfloat)red green:(VGfloat)green blue:(VGfloat)blue alpha:(VGfloat)alpha;

/**
 * Create a color with specific red/green/blue values.
 *
 * @param red Red value for the color.
 * @param green Green value for the color.
 * @param blue Blue value for the color.
 * @param alpha The alpha value for the color.
 * @return The color object created.
 */
+ (KColor *)colorWithDeviceRed:(VGfloat)red green:(VGfloat)green blue:(VGfloat)blue alpha:(VGfloat)alpha;

/**
 * Create an KColor from a hexdecimal value.
 *
 * @param hex The hexdecimal color value.
 * @return returns the KColor created.
 */
+ (KColor *)colorWithHex:(uint)hex;

/**
 * Create a random KColor
 *
 * @return returns the KColor object created.
 */
+ (KColor *)randomColor;

@end