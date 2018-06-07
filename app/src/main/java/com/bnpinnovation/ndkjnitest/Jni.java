package com.bnpinnovation.ndkjnitest;

import android.util.Log;

public class Jni {
    private static Jni me = null;

    public static Jni getJni() {
        if (me != null) return me;
        else me = new Jni();
        return me;
    }

    public static void delJni() {
        if (me != null) me = null;
    }

    private native void jniReqVoid();

    public void reqVoid() {
        jniReqVoid();
    }

    private native int jniReqIntRetInt(int req);

    public int reqIntRetInt(int req) {
        return jniReqIntRetInt(req);
    }

    private native void jniCallBackStart();

    public void callBackStart() {
        jniCallBackStart();
    }

    private native void jniCallBackStop();

    public void callBackStop() {
        jniCallBackStop();
    }

    public static void callbackEventFromNative(Object obj) {
        Log.d("lsc","jniCallBack");
    }



    static {
        System.loadLibrary("ndkjni");
    }
}
