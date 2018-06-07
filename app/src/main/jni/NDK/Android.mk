LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS) $(LOCAL_INCLUDE)

LOCAL_MODULE := ndkjni

MY_MODULES := .

APP_ALLOW_MISSING_DEPS=true

MY_SRCS := $(foreach m,$(MY_MODULES),$(wildcard $(LOCAL_PATH)/$m/*.c))
MY_SRCS += $(foreach m,$(MY_MODULES),$(wildcard $(LOCAL_PATH)/$m/*.cpp))
MY_SRCS := $(subst $(LOCAL_PATH)/,,$(MY_SRCS))

LOCAL_SRC_FILES := $(MY_SRCS)

LOCAL_CFLAGS := -DHAVE_SYS_UIO_H

LOCAL_CFLAGS += -DHAVE_PTHREADS -DPLATFORM_ANDROID -DMB_OS_ANDROID
LOCAL_CFLAGS += -Wno-error=address -Wno-multichar -Wno-psabi -s
LOCAL_CFLAGS += -DMB_OS_ANDROID
LOCAL_CFLAGS += -Wno-write-strings

LOCAL_CFLAGS += -DRV_TOOL_TYPE=RV_TOOL_TYPE_GNU \
             -DRV_TOOL_VERSION=RV_TOOL_GNU_3_4 \
             -DRV_OS_TYPE=RV_OS_TYPE_LINUX \
             -DRV_ARCH_ENDIAN=RV_ARCH_LITTLE_ENDIAN \
             -DRV_OS_VERSION=RV_OS_LINUX_ANDROID \
             -DRV_ARCH_BITS=RV_ARCH_BITS_32 \
             -DRV_ANDROID=1


#MBMEDIA_LDFLAGS += -lgcc

LOCAL_C_INCLUDES += $(LOCAL_PATH)/.

#LOCAL_LDFLAGS += $(MBMEDIA_LDFLAGS)
#LOCAL_LDFLAGS += -L$(APP_PROJECT_PATH)/obj/local/$(TARGET_ARCH_ABI) -lgnustl_static

LOCAL_LDLIBS    += -landroid -llog
LOCAL_LDLIBS    += -Wl,--no-warn-shared-textrel

#ifeq ($(TARGET_ARCH),arm)
	LOCAL_ASFLAGS := -march=armv7-a
#endif

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_CFLAGS += -DHAVE_NEON=1 -DMBAUDIOPRO_ARCH_ARM_NEON -mfpu=neon
    LOCAL_CFLAGS += -mfloat-abi=softfp
endif

#LOCAL_STATIC_LIBRARIES += cpufeatures

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/cpufeatures)