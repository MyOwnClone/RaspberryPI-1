# Initial Setup
-include $(GNUSTEP_MAKEFILES)/common.make

# App Configuration
TOOL_NAME = OpenApp

# Add Includes/Libs
OpenApp_OBJCFLAGS = -I/opt/vc/include
OpenApp_OBJCFLAGS += -I/opt/vc/include/interface/vcos/pthreads
LDFLAGS = -L/opt/vc/lib -lbcm_host -lEGL -lGLESv2 -lOpenVG

# Add Headers
OpenApp_HEADERS = OpenApp.h
OpenApp_HEADERS += TestAppDelegate.h
OpenApp_HEADERS += KDisplayManager.h
OpenApp_HEADERS += KDisplayObject.h

# Add Source Files
OpenApp_OBJC_FILES = main.m
OpenApp_OBJC_FILES += OpenApp.m
OpenApp_OBJC_FILES += TestAppDelegate.m
OpenApp_OBJC_FILES += KDisplayManager.m
OpenApp_OBJC_FILES += KDisplayObject.m

# Add Resources
OpenApp_RESOURCE_FILES = 

# Final
-include GNUmakefile.preamble
-include $(GNUSTEP_MAKEFILES)/tool.make
-include GNUmakefile.postamble
