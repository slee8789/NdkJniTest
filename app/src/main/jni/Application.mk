APP_MODULES += ndkjni

APP_PLATFORM := android-21

APP_STL := gnustl_static

APP_CFLAGS += -Wno-error=format-security

ifeq ($(release), on)
APP_OPTIM = release
APP_CFLAGS += -DRV_RELEASE
else
APP_OPTIM = debug
APP_CFLAGS += -DRV_DEBUG
endif

APP_CPPFLAGS := -fexceptions -Wno-write-strings -Wno-reorder -fpermissive \

APP_ABI := armeabi-v7a

NDK_TOOLCHAIN_VERSION = 4.9