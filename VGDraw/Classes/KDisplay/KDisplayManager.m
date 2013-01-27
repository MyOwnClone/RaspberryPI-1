#import "KDisplayManager.h"
#import "bcm_host.h"
#import <libkern/OSAtomic.h>

@implementation KDisplayManager

static void * volatile sharedInstance = nil;

+ (KDisplayManager *)sharedInstance
{
    while (!sharedInstance)
    {
        KDisplayManager *temp = [[self alloc] init];
        if(!OSAtomicCompareAndSwapPtrBarrier(0x0, temp, &sharedInstance))
        {
            [temp release];
        }
    }
    return sharedInstance;
}

- (void)startUp
{
    
}

- (void)shutDown
{
    
}

@end
