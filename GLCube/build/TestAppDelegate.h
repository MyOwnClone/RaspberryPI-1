#import <Foundation/Foundation.h>
#import "OpenApp.h"
#import "Cube.h"

/**
 * Test OpenGL/OpenVG application.
 *
 * @author Jed Laudenslayer
 */
@interface TestAppDelegate : NSObject <OpenAppDelegate>
{
    Cube *openGLCube_;
}

@end
