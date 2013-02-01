//
//  AppDelegate.h
//  MagnetOS
//
//  Created by Jed Laudenslayer on 1/28/13.
//  Copyright (c) 2013 Jed Laudenslayer. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 * Application delegate.
 *
 * @author Jed Laudenslayer
 */
@interface AppDelegate : UIResponder <UIApplicationDelegate, CBPeripheralManagerDelegate>

/**
 * Main window property for this application.
 */
@property (strong, nonatomic) UIWindow *window;

/**
 * PeripheralManager
 */
@property (strong, nonatomic, readonly) CBPeripheralManager *cbManager;

@end
