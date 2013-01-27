#import "KDisplayManager.h"

#include "bcm_host.h"
#import "EGLState.h"

/**
 * State of the display.
 */
static STATE_T _state, *state = &_state;

@interface KDisplayManager ()



@end

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

- (id)init
{
	self = [super init];

	if (self != nil)
	{
		bcm_host_init();
		memset(state, 0, sizeof(*state));
		oglinit(state);
	}

	return self;
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
