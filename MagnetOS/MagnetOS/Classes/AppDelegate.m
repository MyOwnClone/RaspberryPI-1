//
//  AppDelegate.m
//  MagnetOS
//
//  Created by Jed Laudenslayer on 1/28/13.
//  Copyright (c) 2013 Jed Laudenslayer. All rights reserved.
//

#import "AppDelegate.h"
#import "RootViewController.h"
#import <CoreFoundation/CoreFoundation.h>

#define kMagnetOS_UUID @"649E209C-111B-41D9-B424-F99733B8993F"
#define kCharacteristic_UUID @"3CBCB608-F1AF-4D49-B6D4-05ED0AE235FE"

#define NOTIFY_MTU 20

static BOOL s_sendingEOM = NO;

@interface AppDelegate ()

/**
 * Send end of message.
 */
- (void)sendEndOfMessage;CBUUID

/**
 * Setup the MagnetOS service.
 */
- (void)setupService;

@end

@implementation AppDelegate
{
    CBPeripheralManager *cbManager_;
    CBMutableService *customService_;
    CBMutableCharacteristic *customCharacteristic_;
    NSData *dataToSend_;
    NSInteger sendDataIndex_;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    cbManager_ = [[CBPeripheralManager alloc] initWithDelegate:self queue:nil];
    
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    [self.window setRootViewController:[[RootViewController alloc] init]];
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];
    
    return YES;
}

- (CBPeripheralManager *)cbManager
{
    if (cbManager_ == nil)
    {
        cbManager_ = [[CBPeripheralManager alloc] initWithDelegate:self queue:nil];
        CBCentralManagerScanOptionAllowDuplicatesKey
    }
    
    return cbManager_;
}

- (void)setupService
{
    NSLog(@"Setting up service!");
    
    // Creates the characteristic UUID
    CBUUID *characteristicUUID = [CBUUID UUIDWithString:kCharacteristic_UUID];
    
    // Creates the characteristic
    customCharacteristic_ = [[CBMutableCharacteristic alloc]
                             initWithType:characteristicUUID
                             properties:CBCharacteristicPropertyNotify
                             value:nil
                             permissions:CBAttributePermissionsReadable];
    
    // Creates the service UUID
    CBUUID *serviceUUID = [CBUUID UUIDWithString:kMagnetOS_UUID];
    
    // Creates the service and adds the characteristic to it
    customService_ = [[CBMutableService alloc] initWithType:serviceUUID primary:YES];
    
    // Sets the characteristics for this service
    [customService_ setCharacteristics:@[customCharacteristic_]];
    
    // Publishes the service
    [self.cbManager addService:customService_];
}

#pragma mark - CBPeripheralManagerDelegate

- (void)peripheralManagerDidUpdateState:(CBPeripheralManager *)peripheral
{
    switch (peripheral.state)
    {
        case CBPeripheralManagerStatePoweredOn:
            [self setupService];
            break;
        default:
            NSLog(@"Peripheral Manager did change state");
            break;
    }
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral central:(CBCentral *)central didSubscribeToCharacteristic:(CBCharacteristic *)characteristic
{
    NSLog(@"Central subscribed to characteristic");
    
    dataToSend_ = [@"Hello World!" dataUsingEncoding:NSUTF8StringEncoding];
    sendDataIndex_ = 0;
    
    [self sendData];
}

- (void)peripheralManagerIsReadyToUpdateSubscribers:(CBPeripheralManager *)peripheral
{
    [self sendData];
}

- (void)sendData
{
    if (s_sendingEOM)
    {
        [self sendEndOfMessage];
        return;
    }
    
    // We're not sending an EOM, so we're sending data
    // Is there any left to send?
    
    if (sendDataIndex_ >= dataToSend_.length)
    {
        // --  No More Data
        return;
    }
    
    BOOL didSend = YES;
    
    while (didSend)
    {
        // -- Size of next chunk
        NSInteger amountToSend = dataToSend_.length - sendDataIndex_;
        
        // -- Can't be longer than 20 bytes
        if (amountToSend > NOTIFY_MTU)
        {
            amountToSend = NOTIFY_MTU;
        }
        
        // -- Copy out the data we want
        NSData *chunk = [NSData dataWithBytes:dataToSend_.bytes + sendDataIndex_ length:amountToSend];
        
        // Send it
        didSend = [self.cbManager
                   updateValue:chunk
                   forCharacteristic:customCharacteristic_
                   onSubscribedCentrals:nil];
        
        // -- If it didn't work, drop out and wait for the callback
        if (!didSend) return;
        
        NSString *stringFromData = [[NSString alloc] initWithData:chunk encoding:NSUTF8StringEncoding];
        NSLog(@"Sent: %@", stringFromData);
        
        sendDataIndex_ += amountToSend;
        
        if (sendDataIndex_ >= dataToSend_.length)
        {
            [self sendEndOfMessage];
            return;
        }
    }
}

- (void)sendEndOfMessage
{
    s_sendingEOM = YES;
    BOOL eomSent = [self.cbManager
                    updateValue:[@"EOM" dataUsingEncoding:NSUTF8StringEncoding]
                    forCharacteristic:customCharacteristic_
                    onSubscribedCentrals:nil];
    
    if (eomSent)
    {
        s_sendingEOM = NO;
        NSLog(@"Sent: End Of Message");
    }
}

@end
