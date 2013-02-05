#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <CoreBluetooth/CoreBluetooth.h>

/**
 * Root display view for this application.
 *
 * @author Jed Laudenslayer
 */
@interface AppRootView : CALayer <CBCentralManagerDelegate, CBPeripheralDelegate>
{
    CBCentralManager *cbManager_;
    CBPeripheral *peripheral_;
    NSMutableData *data_;
    CBUUID *serviceID_;
    CBUUID *characteristicID_;
}

@end
