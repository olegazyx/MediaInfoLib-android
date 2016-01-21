APP_PLATFORM := android-9

APP_ABI := armeabi-v7a x86
#APP_ABI := x86

#APP_STL := stlport_static
APP_STL := gnustl_static
#APP_STL := c++_static

#APP_OPTIM := debug

APP_CFLAGS += -Os -fvisibility=hidden
APP_CPPFLAGS += -fexceptions -fvisibility=hidden
