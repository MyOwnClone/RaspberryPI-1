#import "KDisplayObject.h"

@implementation KDisplayObject

@synthesize width = width_;
@synthesize height = height_;
@synthesize backgroundColor = backgroundColor_;

- (id)init
{
	self = [super init];
	
	if (self != nil)
	{
		
	}
	
	return self;
}

- (void)dealloc
{
	[backgroundColor_ release];
	[super dealloc];
}

- (void)render
{
	
}

@end
