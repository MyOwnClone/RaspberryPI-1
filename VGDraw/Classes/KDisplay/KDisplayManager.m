#import "KDisplayManager.h"

#import "bcm_host.h"
#import "EGLState.h"

/**
 * State of the display.
 */
static STATE_T _state, *state = &_state;

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

- (void)dealloc
{
	eglSwapBuffers(state->display, state->surface);
	
	[super dealloc];
}

- (void)loadRootDisplayObject:(KDisplayObject *)displayObject
{
	if (rootObject_ != nil)
	{
		[rootObject_ release];
		rootObject_ = nil;
	}

	rootObject_ = [displayObject retain];
	
	rootObject_.width = (float)state->screen_width;
	rootObject_.height = (float)state->screen_height;
}

- (void)loop
{
	if (rootObject_ != nil)
	{
		[rootObject_ render];
		eglSwapBuffers(state->display, state->surface);
	}

	usleep(5*1000);
}

@end
