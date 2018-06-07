LOCAL_PATH := $(call my-dir)
NDKMODULES := NDK

include $(foreach m,$(NDKMODULES),$(LOCAL_PATH)/$m/Android.mk)