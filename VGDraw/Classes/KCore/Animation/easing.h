// TERMS OF USE - EASING EQUATIONS
//
// Open source under the BSD License. 
//
// Copyright © 2001 Robert Penner
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer 
// in the documentation and/or other materials provided with the distribution. Neither the name of the author nor the names of 
// contributors may be used to endorse or promote products derived from this software without specific prior written permission.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, 
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
// OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "VG/openvg.h"
#include "VG/vgu.h"

#include <math.h>

typedef VGfloat (*AHEasingFunction)(VGfloat);

// Linear interpolation (no easing)
VGfloat LinearInterpolation(VGfloat p);

// Quadratic easing; p^2
VGfloat QuadraticEaseIn(VGfloat p);
VGfloat QuadraticEaseOut(VGfloat p);
VGfloat QuadraticEaseInOut(VGfloat p);

// Cubic easing; p^3
VGfloat CubicEaseIn(VGfloat p);
VGfloat CubicEaseOut(VGfloat p);
VGfloat CubicEaseInOut(VGfloat p);

// Quartic easing; p^4
VGfloat QuarticEaseIn(VGfloat p);
VGfloat QuarticEaseOut(VGfloat p);
VGfloat QuarticEaseInOut(VGfloat p);

// Quintic easing; p^5
VGfloat QuinticEaseIn(VGfloat p);
VGfloat QuinticEaseOut(VGfloat p);
VGfloat QuinticEaseInOut(VGfloat p);

// Sine wave easing; sin(p * PI/2)
VGfloat SineEaseIn(VGfloat p);
VGfloat SineEaseOut(VGfloat p);
VGfloat SineEaseInOut(VGfloat p);

// Circular easing; sqrt(1 - p^2)
VGfloat CircularEaseIn(VGfloat p);
VGfloat CircularEaseOut(VGfloat p);
VGfloat CircularEaseInOut(VGfloat p);

// Exponential easing, base 2
VGfloat ExponentialEaseIn(VGfloat p);
VGfloat ExponentialEaseOut(VGfloat p);
VGfloat ExponentialEaseInOut(VGfloat p);

// Exponentially-damped sine wave easing
VGfloat ElasticEaseIn(VGfloat p);
VGfloat ElasticEaseOut(VGfloat p);
VGfloat ElasticEaseInOut(VGfloat p);

// Overshooting cubic easing;
VGfloat BackEaseIn(VGfloat p);
VGfloat BackEaseOut(VGfloat p);
VGfloat BackEaseInOut(VGfloat p);

// Exponentially-decaying bounce easing
VGfloat BounceEaseIn(VGfloat p);
VGfloat BounceEaseOut(VGfloat p);
VGfloat BounceEaseInOut(VGfloat p);

// Modeled after the line y = x
VGfloat LinearInterpolation(VGfloat p)
{
    return p;
}

// Modeled after the parabola y = x^2
VGfloat QuadraticEaseIn(VGfloat p)
{
    return p * p;
}

// Modeled after the parabola y = -x^2 + 2x
VGfloat QuadraticEaseOut(VGfloat p)
{
    return -(p * (p - 2));
}

// Modeled after the piecewise quadratic
// y = (1/2)((2x)^2)             ; [0, 0.5)
// y = -(1/2)((2x-1)*(2x-3) - 1) ; [0.5, 1]
VGfloat QuadraticEaseInOut(VGfloat p)
{
    if(p < 0.5)
    {
        return 2 * p * p;
    }
    else
    {
        return (-2 * p * p) + (4 * p) - 1;
    }
}

// Modeled after the cubic y = x^3
VGfloat CubicEaseIn(VGfloat p)
{
    return p * p * p;
}

// Modeled after the cubic y = (x - 1)^3 + 1
VGfloat CubicEaseOut(VGfloat p)
{
    VGfloat f = (p - 1);
    return f * f * f + 1;
}

// Modeled after the piecewise cubic
// y = (1/2)((2x)^3)       ; [0, 0.5)
// y = (1/2)((2x-2)^3 + 2) ; [0.5, 1]
VGfloat CubicEaseInOut(VGfloat p)
{
    if(p < 0.5)
    {
        return 4 * p * p * p;
    }
    else
    {
        VGfloat f = ((2 * p) - 2);
        return 0.5 * f * f * f + 1;
    }
}

// Modeled after the quartic x^4
VGfloat QuarticEaseIn(VGfloat p)
{
    return p * p * p * p;
}

// Modeled after the quartic y = 1 - (x - 1)^4
VGfloat QuarticEaseOut(VGfloat p)
{
    VGfloat f = (p - 1);
    return f * f * f * (1 - p) + 1;
}

// Modeled after the piecewise quartic
// y = (1/2)((2x)^4)        ; [0, 0.5)
// y = -(1/2)((2x-2)^4 - 2) ; [0.5, 1]
VGfloat QuarticEaseInOut(VGfloat p)
{
    if(p < 0.5)
    {
        return 8 * p * p * p * p;
    }
    else
    {
        VGfloat f = (p - 1);
        return -8 * f * f * f * f + 1;
    }
}

// Modeled after the quintic y = x^5
VGfloat QuinticEaseIn(VGfloat p)
{
    return p * p * p * p * p;
}

// Modeled after the quintic y = (x - 1)^5 + 1
VGfloat QuinticEaseOut(VGfloat p)
{
    VGfloat f = (p - 1);
    return f * f * f * f * f + 1;
}

// Modeled after the piecewise quintic
// y = (1/2)((2x)^5)       ; [0, 0.5)
// y = (1/2)((2x-2)^5 + 2) ; [0.5, 1]
VGfloat QuinticEaseInOut(VGfloat p)
{
    if(p < 0.5)
    {
        return 16 * p * p * p * p * p;
    }
    else
    {
        VGfloat f = ((2 * p) - 2);
        return  0.5 * f * f * f * f * f + 1;
    }
}

// Modeled after quarter-cycle of sine wave
VGfloat SineEaseIn(VGfloat p)
{
    return sin((p - 1) * M_PI_2) + 1;
}

// Modeled after quarter-cycle of sine wave (different phase)
VGfloat SineEaseOut(VGfloat p)
{
    return sin(p * M_PI_2);
}

// Modeled after half sine wave
VGfloat SineEaseInOut(VGfloat p)
{
    return 0.5 * (1 - cos(p * M_PI));
}

// Modeled after shifted quadrant IV of unit circle
VGfloat CircularEaseIn(VGfloat p)
{
    return 1 - sqrt(1 - (p * p));
}

// Modeled after shifted quadrant II of unit circle
VGfloat CircularEaseOut(VGfloat p)
{
    return sqrt((2 - p) * p);
}

// Modeled after the piecewise circular function
// y = (1/2)(1 - sqrt(1 - 4x^2))           ; [0, 0.5)
// y = (1/2)(sqrt(-(2x - 3)*(2x - 1)) + 1) ; [0.5, 1]
VGfloat CircularEaseInOut(VGfloat p)
{
    if(p < 0.5)
    {
        return 0.5 * (1 - sqrt(1 - 4 * (p * p)));
    }
    else
    {
        return 0.5 * (sqrt(-((2 * p) - 3) * ((2 * p) - 1)) + 1);
    }
}

// Modeled after the exponential function y = 2^(10(x - 1))
VGfloat ExponentialEaseIn(VGfloat p)
{
    return (p == 0.0) ? p : pow(2, 10 * (p - 1));
}

// Modeled after the exponential function y = -2^(-10x) + 1
VGfloat ExponentialEaseOut(VGfloat p)
{
    return (p == 1.0) ? p : 1 - pow(2, -10 * p);
}

// Modeled after the piecewise exponential
// y = (1/2)2^(10(2x - 1))         ; [0,0.5)
// y = -(1/2)*2^(-10(2x - 1))) + 1 ; [0.5,1]
VGfloat ExponentialEaseInOut(VGfloat p)
{
    if(p == 0.0 || p == 1.0) return p;
    
    if(p < 0.5)
    {
        return 0.5 * pow(2, (20 * p) - 10);
    }
    else
    {
        return -0.5 * pow(2, (-20 * p) + 10) + 1;
    }
}

// Modeled after the damped sine wave y = sin(13pi/2*x)*pow(2, 10 * (x - 1))
VGfloat ElasticEaseIn(VGfloat p)
{
    return sin(13 * M_PI_2 * p) * pow(2, 10 * (p - 1));
}

// Modeled after the damped sine wave y = sin(-13pi/2*(x + 1))*pow(2, -10x) + 1
VGfloat ElasticEaseOut(VGfloat p)
{
    return sin(-13 * M_PI_2 * (p + 1)) * pow(2, -10 * p) + 1;
}

// Modeled after the piecewise exponentially-damped sine wave:
// y = (1/2)*sin(13pi/2*(2*x))*pow(2, 10 * ((2*x) - 1))      ; [0,0.5)
// y = (1/2)*(sin(-13pi/2*((2x-1)+1))*pow(2,-10(2*x-1)) + 2) ; [0.5, 1]
VGfloat ElasticEaseInOut(VGfloat p)
{
    if(p < 0.5)
    {
        return 0.5 * sin(13 * M_PI_2 * (2 * p)) * pow(2, 10 * ((2 * p) - 1));
    }
    else
    {
        return 0.5 * (sin(-13 * M_PI_2 * ((2 * p - 1) + 1)) * pow(2, -10 * (2 * p - 1)) + 2);
    }
}

// Modeled after the overshooting cubic y = x^3-x*sin(x*pi)
VGfloat BackEaseIn(VGfloat p)
{
    return p * p * p - p * sin(p * M_PI);
}

// Modeled after overshooting cubic y = 1-((1-x)^3-(1-x)*sin((1-x)*pi))
VGfloat BackEaseOut(VGfloat p)
{
    VGfloat f = (1 - p);
    return 1 - (f * f * f - f * sin(f * M_PI));
}

// Modeled after the piecewise overshooting cubic function:
// y = (1/2)*((2x)^3-(2x)*sin(2*x*pi))           ; [0, 0.5)
// y = (1/2)*(1-((1-x)^3-(1-x)*sin((1-x)*pi))+1) ; [0.5, 1]
VGfloat BackEaseInOut(VGfloat p)
{
    if(p < 0.5)
    {
        VGfloat f = 2 * p;
        return 0.5 * (f * f * f - f * sin(f * M_PI));
    }
    else
    {
        VGfloat f = (1 - (2*p - 1));
        return 0.5 * (1 - (f * f * f - f * sin(f * M_PI))) + 0.5;
    }
}

VGfloat BounceEaseIn(VGfloat p)
{
    return 1 - BounceEaseOut(1 - p);
}

VGfloat BounceEaseOut(VGfloat p)
{
    if(p < 4/11.0)
    {
        return (121 * p * p)/16.0;
    }
    else if(p < 8/11.0)
    {
        return (363/40.0 * p * p) - (99/10.0 * p) + 17/5.0;
    }
    else if(p < 9/10.0)
    {
        return (4356/361.0 * p * p) - (35442/1805.0 * p) + 16061/1805.0;
    }
    else
    {
        return (54/5.0 * p * p) - (513/25.0 * p) + 268/25.0;
    }
}

VGfloat BounceEaseInOut(VGfloat p)
{
    if(p < 0.5)
    {
        return 0.5 * BounceEaseIn(p*2);
    }
    else
    {
        return 0.5 * BounceEaseOut(p * 2 - 1) + 0.5;
    }
}