//
// Created by 이승철 on 2018. 6. 1..
//

#include <jni.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <android/log.h>
#include <pthread.h>
#include "NDK.h"

static const char* const classPath = "com/bnpinnovation/ndkjnitest/Jni";

static JavaVM    *gJavaVM;
static jclass	 mDevice;
static jclass    mClass;
static jobject   mObject;
bool bStartCallBackThread = false;
pthread_t mCallBackThread = 0;
jmethodID callback_event;
void*  CallBackThread(void* lParam);

void com_bnpinnovation_ndkjnitest_Jni_jniReqVoid(JNIEnv*  env, jobject  thiz) {
  __android_log_print(ANDROID_LOG_DEBUG, "JNI jniReqVoid", "START");
  jniReqVoid();
  __android_log_print(ANDROID_LOG_DEBUG, "JNI jniReqVoid", "END");
}

void jniReqVoid(void) {
    __android_log_print(ANDROID_LOG_DEBUG, "NDK jniReqVoid", "START");
    __android_log_print(ANDROID_LOG_DEBUG, "NDK jniReqVoid", "END");
}

int com_bnpinnovation_ndkjnitest_Jni_jniReqIntRetInt(JNIEnv*  env, jobject  thiz, jint jReq) {
  __android_log_print(ANDROID_LOG_DEBUG, "JNI jniReqIntRetInt", "START");
  __android_log_print(ANDROID_LOG_DEBUG, "JNI jniReqIntRetInt", "END");
  return jniReqIntRetInt(jReq);
}

int jniReqIntRetInt(int req) {
    __android_log_print(ANDROID_LOG_DEBUG, "NDK jniReqIntRetInt", "START");
    __android_log_print(ANDROID_LOG_DEBUG, "NDK jniReqIntRetInt", "END");
    return req;
}

void com_bnpinnovation_ndkjnitest_Jni_jniCallBackStart(JNIEnv*  env, jobject thiz) {
   __android_log_print(ANDROID_LOG_DEBUG, "JNI jniCallBackStart", "START");
   __android_log_print(ANDROID_LOG_DEBUG, "JNI jniCallBackStart", "END");
   //jniCallBackStart();
   jclass clazz = env->GetObjectClass(thiz);
   mClass = (jclass)env->NewGlobalRef(clazz);
   callback_event = env->GetStaticMethodID(clazz, "callbackEventFromNative", "(Ljava/lang/Object;)V");
   bStartCallBackThread = true;
   pthread_create(&mCallBackThread, NULL, CallBackThread, (void*)NULL);
 }

 void jniCallBackStart(void) {
     __android_log_print(ANDROID_LOG_DEBUG, "NDK jniCallBackStart", "START");
     __android_log_print(ANDROID_LOG_DEBUG, "NDK jniCallBackStart", "END");

 }

 void CallbackNotify()
  {
    int status = 0;
    JNIEnv* env = NULL;
    bool bAttach = false;

    if (gJavaVM->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
      bAttach = true;
    if(bAttach)
      status = gJavaVM->AttachCurrentThread(&env, NULL);

    env->CallStaticVoidMethod(mClass, callback_event, mObject);

    if(bAttach)
      gJavaVM->DetachCurrentThread();
  }

 void* CallBackThread(void* lParam) {
    while(bStartCallBackThread) {
    	CallbackNotify();
    	usleep(1000*1000);
    	}
    	return NULL;
 }

 void com_bnpinnovation_ndkjnitest_Jni_jniCallBackStop(JNIEnv*  env, jobject) {
   __android_log_print(ANDROID_LOG_DEBUG, "JNI jniCallBackStop", "START");
   __android_log_print(ANDROID_LOG_DEBUG, "JNI jniCallBackStop", "END");
   jniCallBackStop();
 }

 void jniCallBackStop(void) {
     __android_log_print(ANDROID_LOG_DEBUG, "NDK jniCallBackStop", "START");
     __android_log_print(ANDROID_LOG_DEBUG, "NDK jniCallBackStop", "END");
     bStartCallBackThread = false;
     int* status;
     pthread_join(mCallBackThread, (void **)&status);
     mCallBackThread = 0;
 }


static JNINativeMethod gMethods[] = {
	{"jniReqVoid",      "()V",           (void *)com_bnpinnovation_ndkjnitest_Jni_jniReqVoid},
	{"jniReqIntRetInt",      "(I)I",           (void *)com_bnpinnovation_ndkjnitest_Jni_jniReqIntRetInt},
	{"jniCallBackStart",      "()V",           (void *)com_bnpinnovation_ndkjnitest_Jni_jniCallBackStart},
	{"jniCallBackStop",      "()V",           (void *)com_bnpinnovation_ndkjnitest_Jni_jniCallBackStop}
};

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
  int status = -1;
  JNIEnv* env = NULL;
  jclass cls;

  if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
    return status;
  }

  cls = env->FindClass(classPath);
  if (cls == 0) {
    return status;
  }

  if (env->RegisterNatives(cls, gMethods, sizeof(gMethods)/sizeof(gMethods[0])) < 0) {
    return status;
  }

  gJavaVM = vm;
  status = JNI_VERSION_1_4;

  return status;
}