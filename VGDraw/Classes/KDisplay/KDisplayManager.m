#import "KDisplayManager.h"
#import "bcm_host.h"

@implementation KDisplayManager

static void * volatile sharedInstance = nil;

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

- (void)startUp
{

}

- (void)shutDown
{

}

@end
