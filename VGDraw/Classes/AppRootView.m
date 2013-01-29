#import "AppRootView.h"

static VGfloat s_shift = 0.0f;
static BOOL s_reverse = NO;

@implementation AppRootView

- (id)init
{
	self = [super init];
	
	if (self != nil)
	{
		self.backgroundColor = [KColor colorWithHex:0xffA3BEFF];
	}
	
	return self;
}

- (void)render
{
	[super render];
	
	VGfloat color[4] = { self.backgroundColor.red, 
			self.backgroundColor.green, 
			self.backgroundColor.blue, 
			s_shift };
			
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
		self.backgroundColor = [KColor randomColor];
	}
}

@end