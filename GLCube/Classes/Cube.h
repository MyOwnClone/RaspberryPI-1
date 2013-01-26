#import <Foundation/Foundation.h>

#import "GLES/gl.h"
#import "EGL/egl.h"
#import "EGL/eglext.h"

typedef struct
{
   uint32_t screen_width;
   uint32_t screen_height;
// OpenGL|ES objects
   EGLDisplay display;
   EGLSurface surface;
   EGLContext context;
   GLuint tex[6];
// model rotation vector and direction
   GLfloat rot_angle_x_inc;
   GLfloat rot_angle_y_inc;
   GLfloat rot_angle_z_inc;
// current model rotation angles
   GLfloat rot_angle_x;
   GLfloat rot_angle_y;
   GLfloat rot_angle_z;
// current distance from camera
   GLfloat distance;
   GLfloat distance_inc;
// pointers to texture buffers
   char *tex_buf1;
   char *tex_buf2;
   char *tex_buf3;
} CUBE_STATE_T;

/**
 * Used to display an OpenGL cube
 *
 * @author Jed Laudenslayer
 */
@interface Cube : NSObject

/**
 * Used to start the cube.
 */
- (void)start;

/**
 * Used for the rendering loop.
 */
- (void)loop;

@end
