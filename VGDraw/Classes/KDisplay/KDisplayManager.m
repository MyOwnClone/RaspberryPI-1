#import "KDisplayManager.h"
#import "bcm_host.h"

@implementation KDisplayManager

static void *volatile sharedInstance = nil;

+ (KDisplayManager *)sharedInstance
{
	static KDisplayManager *singleton = nil;

	if (!singleton)
	{
		@synchronized(self)
		{
			if (!singleton)
			{
				singleton = [KDisplayManager new];
			}
		}
	}

	return singleton;
}

- (void)loadRootDisplayObject:(KDisplayObject *)displayObject
{
	NSLog(@"loadRootDisplayObject: %@", displayObject);

	if (rootObject_ != nil)
	{
		[rootObject_ release];
		rootObject_ = nil;
	}

	rootObject_ = [displayObject retain];
}

- (void)loop
{
	if (rootObject_ != nil)
	{
		// Process all view rendering here.
	}

	// This may need to be modified?
	usleep(5*1000);
}

@end
