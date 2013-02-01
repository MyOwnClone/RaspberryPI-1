#import "KDisplayManager.h"

#import "bcm_host.h"
#import "EGLState.h"

//! State of the display.
static STATE_T _state, *state = &_state;

//! Singleton instance
static void *volatile sharedInstance = nil;

@implementation KDisplayManager

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

- (void)loadRootLayer:(CALayer *)layer
{
    if (rootLayer_ != nil)
    {
        [rootLayer_ release];
        rootLayer_ = nil;
    }

    rootLayer_ = [layer retain];
    
    //rootLayer_.width = (float)state->screen_width;
    //rootLayer_.height = (float)state->screen_height;
}

- (void)loop
{
    if (rootLayer_ != nil)
    {
        //[rootLayer_ render];
        eglSwapBuffers(state->display, state->surface);
    }

    usleep(5*1000);
}

@end
