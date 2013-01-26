# Initial Setup
-include $(GNUSTEP_MAKEFILES)/common.make

# App Configuration
TOOL_NAME = OpenApp

# Add Includes/Libs
OpenApp_OBJCFLAGS = -I/opt/vc/include
OpenApp_OBJCFLAGS += -I/opt/vc/include/interface/vcos/pthreads
LDFLAGS = -L/opt/vc/lib -lbcm_host -lEGL -lGLESv2

# Add Headers
OpenApp_HEADERS = OpenApp.h
OpenApp_HEADERS += TestAppDelegate.h
OpenApp_HEADERS += Cube.h
OpenApp_HEADERS += cube_texture_and_coords.h  

# Add Source Files
OpenApp_OBJC_FILES = main.m
OpenApp_OBJC_FILES += OpenApp.m
OpenApp_OBJC_FILES += TestAppDelegate.m
OpenApp_OBJC_FILES += Cube.m

# Add Resources
OpenApp_RESOURCE_FILES = Djenne_128_128.raw
OpenApp_RESOURCE_FILES += Gaudi_128_128.raw
OpenApp_RESOURCE_FILES += Lucca_128_128.raw

# Final
-include GNUmakefile.preamble
-include $(GNUSTEP_MAKEFILES)/tool.make
-include GNUmakefile.postamble
