#import "KDisplayObject.h"

#include "VG/openvg.h"
#include "VG/vgu.h"

@implementation KDisplayObject

@synthesize width = width_;
@synthesize height = height_;

- (void)render
{
	if (!skipRedraw_)
	{
		VGfloat color[4] = { 255, 255, 255, 1 };
		vgSetfv(VG_CLEAR_COLOR, 4, color);
		vgClear(0, 0, width_, height_);
		
		skipRedraw_ = YES;
	}
}

@end
