//
//  RootViewController.m
//  MagnetOS
//
//  Created by Jed Laudenslayer on 1/28/13.
//  Copyright (c) 2013 Jed Laudenslayer. All rights reserved.
//

#import "RootViewController.h"

@interface RootViewController ()
{
    
}

@end

@implementation RootViewController

- (id)init
{
    self = [super init];
    
    if (self != nil)
    {
        
    }
    
    return self;
}

- (void)loadView
{
    self.view = [[UIView alloc] initWithFrame:[UIScreen mainScreen].bounds];
    
    // -- TODO: Setup gestures
}

@end
