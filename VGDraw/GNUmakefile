ifeq ($(GNUSTEP_MAKEFILES),)
 GNUSTEP_MAKEFILES := $(shell gnustep-config --variable=GNUSTEP_MAKEFILES 2>/dev/null)
  ifeq ($(GNUSTEP_MAKEFILES),)
    $(warning )
    $(warning Unable to obtain GNUSTEP_MAKEFILES setting from gnustep-config!)
    $(warning Perhaps gnustep-make is not properly installed,)
    $(warning so gnustep-config is not in your PATH.)
    $(warning )
    $(warning Your PATH is currently $(PATH))
    $(warning )
  endif
endif

ifeq ($(GNUSTEP_MAKEFILES),)
  $(error You need to set GNUSTEP_MAKEFILES before compiling!)
endif

# Initial Setup
-include $(GNUSTEP_MAKEFILES)/common.make

# App Configuration
TOOL_NAME = OpenApp

# Add Includes/Libs
OpenApp_OBJCFLAGS = -I/opt/vc/include
OpenApp_OBJCFLAGS += -I/opt/vc/include/interface/vcos/pthreads
LDFLAGS = -L/opt/vc/lib -lbcm_host -lEGL -lGLESv2 -lOpenVG -lQuartzCore -lCoreBluetooth -lbluetooth 

# Add Headers
OpenApp_HEADERS = OpenApp.h
OpenApp_HEADERS += easing.h
OpenApp_HEADERS += AppRootView.h
OpenApp_HEADERS += EGLState.h
OpenApp_HEADERS += TestAppDelegate.h
OpenApp_HEADERS += KDisplayManager.h
OpenApp_HEADERS += KColor.h

# Add Source Files
OpenApp_OBJC_FILES = main.m
OpenApp_OBJC_FILES += OpenApp.m
OpenApp_OBJC_FILES += AppRootView.m
OpenApp_OBJC_FILES += TestAppDelegate.m
OpenApp_OBJC_FILES += KDisplayManager.m
OpenApp_OBJC_FILES += KColor.m

# Add Resources
OpenApp_RESOURCE_FILES = 

# Final
-include GNUmakefile.preamble
-include $(GNUSTEP_MAKEFILES)/tool.make
-include GNUmakefile.postamble
