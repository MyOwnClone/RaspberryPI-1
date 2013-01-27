#import "KDisplayObject.h"

static VGfloat s_shift = 0.0f;
static BOOL s_reverse = NO;

@implementation KDisplayObject

@synthesize width = width_;
@synthesize height = height_;

- (void)render
{
	VGfloat color[4] = { s_shift, s_shift, s_shift, 1.0f };
	vgSetfv(VG_CLEAR_COLOR, 4, color);
	vgClear(0, 0, width_, height_);
	vgFlush();
	
	if (!s_reverse)
	{
		s_shift += 0.01f;
	}
	else
	{
		s_shift -= 0.01f;
	}
	
	if (s_shift >= 1.0)
	{
		s_reverse = YES;
	}
	else if (s_shift <= 0.0)
	{
		s_reverse = NO;
	}
}

@end
