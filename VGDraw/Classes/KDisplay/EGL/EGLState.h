// Copyright (C) 2012 Anthony Starks
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
// and associated documentation files (the "Software"), to deal in the Software without 
// restriction, including without limitation the rights to use, copy, modify, merge, publish, 
// distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
// AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#import "EGL/egl.h"
#import "GLES/gl.h"
#import "bcm_host.h"
#import <assert.h>

typedef struct
{
    uint32_t screen_width;
    uint32_t screen_height;

    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;

} STATE_T;

extern void oglinit(STATE_T *);
extern void oglinit(STATE_T *state) {
    int32_t success = 0;
    EGLBoolean result;
    EGLint num_config;

    static EGL_DISPMANX_WINDOW_T nativewindow;

    DISPMANX_ELEMENT_HANDLE_T dispman_element;
    DISPMANX_DISPLAY_HANDLE_T dispman_display;
    DISPMANX_UPDATE_HANDLE_T dispman_update;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;

    static const EGLint attribute_list[] = {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_NONE
    };

    EGLConfig config;

    // get an EGL display connection
    state->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    assert(state->display != EGL_NO_DISPLAY);

    // initialize the EGL display connection
    result = eglInitialize(state->display, NULL, NULL);
    assert(EGL_FALSE != result);

    // bind OpenVG API
    eglBindAPI(EGL_OPENVG_API);

    // get an appropriate EGL frame buffer configuration
    result = eglChooseConfig(state->display, attribute_list, &config, 1, &num_config);
    assert(EGL_FALSE != result);

    // create an EGL rendering context
    state->context = eglCreateContext(state->display, config, EGL_NO_CONTEXT, NULL);
    assert(state->context != EGL_NO_CONTEXT);

    // create an EGL window surface
    success = graphics_get_display_size(0 /* LCD */ , &state->screen_width,
                        &state->screen_height);
    assert(success >= 0);

    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.width = state->screen_width;
    dst_rect.height = state->screen_height;

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.width = state->screen_width << 16;
    src_rect.height = state->screen_height << 16;

    dispman_display = vc_dispmanx_display_open(0 /* LCD */ );
    dispman_update = vc_dispmanx_update_start(0);

    dispman_element = vc_dispmanx_element_add(dispman_update, dispman_display, 0 /*layer */ , &dst_rect, 0 /*src */ ,
                          &src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha */ , 0 /*clamp */ ,
                          0 /*transform */ );

    nativewindow.element = dispman_element;
    nativewindow.width = state->screen_width;
    nativewindow.height = state->screen_height;
    vc_dispmanx_update_submit_sync(dispman_update);

    state->surface = eglCreateWindowSurface(state->display, config, &nativewindow, NULL);
    assert(state->surface != EGL_NO_SURFACE);

    // preserve the buffers on swap
    result = eglSurfaceAttrib(state->display, state->surface, EGL_SWAP_BEHAVIOR, EGL_BUFFER_PRESERVED);
    assert(EGL_FALSE != result);

    // connect the context to the surface
    result = eglMakeCurrent(state->display, state->surface, state->surface, state->context);
    assert(EGL_FALSE != result);

    // set up screen ratio
    glViewport(0, 0, (GLsizei) state->screen_width, (GLsizei) state->screen_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float ratio = (float)state->screen_width / (float)state->screen_height;
    glFrustumf(-ratio, ratio, -1.0f, 1.0f, 1.0f, 10.0f);
}
