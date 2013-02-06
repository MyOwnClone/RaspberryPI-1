#import "AppRootView.h"

#define kMagnetOS_UUID @"649E209C-111B-41D9-B424-F99733B8993F"
#define kCharacteristic_UUID @"3CBCB608-F1AF-4D49-B6D4-05ED0AE235FE"

@implementation AppRootView

- (id)init
{
    self = [super init];
    
    if (self != nil)
    {
        NSLog(@"Create Data!");
        data_ = [[NSMutableData alloc] init];
        NSLog(@"Create cbManager_!");
        cbManager_ = [[CBCentralManager alloc] initWithDelegate:self];
        NSLog(@"Create serviceID_!");
        serviceID_ = [[CBUUID UUIDWithString:kMagnetOS_UUID] retain];
        NSLog(@"Create characteristicID_!");
        characteristicID_ = [[CBUUID UUIDWithString:kCharacteristic_UUID] retain];
        
        NSLog(@"serviceID_: %@ \n", serviceID_);
        NSLog(@"characteristicID_: %@ \n", characteristicID_);
    }
    
    return self;
}

- (void)dealloc
{
    [cbManager_ release];
    cbManager_ = nil;
    
    [data_ release];
    data_ = nil;
    
    [peripheral_ release];
    peripheral_ = nil;
    
    [serviceID_ release];
    serviceID_ = nil;
    
    [characteristicID_ release];
    characteristicID_ = nil;
    
    [super dealloc];
}

- (void)centralManagerDidUpdateState:(CBCentralManager *)central
{
    switch (central.state)
    {
        case CBCentralManagerStatePoweredOn:
        {
            // NSDictionary *options = [NSDictionary 
            //     dictionaryWithObject:[NSNumber numberWithBool:YES] 
            //     forKey:CBCentralManagerScanOptionAllowDuplicatesKey];
                
            // Scans for any peripheral
            [central scanForPeripheralsWithServices:[NSArray arrayWithObject:serviceID_] options:nil];
                
            break;
        }
        
        default:
        {
            NSLog(@"Central Manager did change state");
            break;
        }
    }
}

- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral 
                                        advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI
{
    // Stops scanning for peripheral
    [central stopScan];
    
    if (peripheral_ != peripheral)
    {
        if (peripheral_ != nil)
        {
            [peripheral_ release];
            peripheral_ = nil;
        }
        
        peripheral_ = [peripheral_ retain];
        [central connectPeripheral:peripheral_ options:nil];
    }
}

- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral
{
    // Clears the data that we may already have
    [data_ setLength:0];
    // Sets the peripheral delegate
    [peripheral_ setDelegate:self];
    // Asks the peripheral to discover the service
    [peripheral_ discoverServices:[NSArray arrayWithObject:serviceID_]];
}

- (void)peripheral:(CBPeripheral *)aPeripheral didDiscoverServices:(NSError *)error
{
    if (error)
    {
        NSLog(@"Error discovering service: %@", [error localizedDescription]);
        return;
    }

    for (CBService *service in aPeripheral.services)
    {
        NSLog(@"Service found with UUID: %@", service.UUID);

        // Discovers the characteristics for a given service
        if ([service.UUID isEqual:serviceID_])
        {
            [peripheral_ discoverCharacteristics:[NSArray arrayWithObject:characteristicID_] forService:service];
        }
    }
}

- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error
{
    if (error)
    {
        NSLog(@"Error discovering characteristic: %@", [error localizedDescription]);
        return;
    }
    
    if ([service.UUID isEqual:serviceID_])
    {
        for (CBCharacteristic *characteristic in service.characteristics)
        {
            if ([characteristic.UUID isEqual:characteristicID_])
            {
                [peripheral setNotifyValue:YES forCharacteristic:characteristic];
            }
        }
    }
}

- (void)peripheral:(CBPeripheral *)peripheral didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error
{
    if (error)
    {
        NSLog(@"Error changing notification state: %@", error.localizedDescription);
    }

    // Exits if it's not the transfer characteristic
    if (![characteristic.UUID isEqual:characteristicID_])
    {
        return;
    }

    // Notification has started
    if (characteristic.isNotifying)
    {
        NSLog(@"Notification began on %@", characteristic);
        [peripheral readValueForCharacteristic:characteristic];
    }
    else
    { 
        // Notification has stopped
        // so disconnect from the peripheral
        NSLog(@"Notification stopped on %@.  Disconnecting", characteristic);
        [cbManager_ cancelPeripheralConnection:peripheral];
    }
}

@end