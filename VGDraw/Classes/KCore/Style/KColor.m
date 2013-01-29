#import "KColor.h"

@implementation KColor

@synthesize red = red_;
@synthesize green = green_;
@synthesize blue = blue_;
@synthesize alpha = alpha_;

- (KColor *)initWithDeviceRed:(VGfloat)red green:(VGfloat)green blue:(VGfloat)blue alpha:(VGfloat)alpha
{
    self = [super init];
    
    if (self != nil)
    {
        self.red = red;
        self.green = green;
        self.blue = blue;
        self.alpha = alpha;
    }
    
    return self;
}

+ (KColor *)colorWithDeviceRed:(VGfloat)red green:(VGfloat)green blue:(VGfloat)blue alpha:(VGfloat)alpha
{
    return [[[KColor alloc] initWithDeviceRed:red green:green blue:blue alpha:alpha] autorelease];
}

+ (KColor *)colorWithHex:(uint)hex
{
    int red, green, blue, alpha;

    blue = hex & 0x000000FF;
    green = ((hex & 0x0000FF00) >> 8);
    red = ((hex & 0x00FF0000) >> 16);
    alpha = ((hex & 0xFF000000) >> 24);

    return [KColor colorWithDeviceRed:red/255.0f green:green/255.0f blue:blue/255.0f alpha:alpha/255.f];
}

+ (KColor *)randomColor
{
    CGFloat red =  (CGFloat)random()/(CGFloat)RAND_MAX;
    CGFloat blue = (CGFloat)random()/(CGFloat)RAND_MAX;
    CGFloat green = (CGFloat)random()/(CGFloat)RAND_MAX;

    return [KColor colorWithDeviceRed:red green:green blue:blue alpha:1.0];
}

@end