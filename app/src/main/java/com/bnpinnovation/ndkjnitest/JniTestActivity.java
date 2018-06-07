package com.bnpinnovation.ndkjnitest;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

public class JniTestActivity extends AppCompatActivity implements View.OnClickListener {

    Jni jni = Jni.getJni();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.btnJniReqVoid).setOnClickListener(this);
        findViewById(R.id.btnJniReqIntReturnInt).setOnClickListener(this);
        findViewById(R.id.btnJniCallBackStart).setOnClickListener(this);
        findViewById(R.id.btnJniCallBackStop).setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btnJniReqVoid:
                jni.reqVoid();
                break;
            case R.id.btnJniReqIntReturnInt:
                Log.d("lsc","return value is " + jni.reqIntRetInt(5));
                break;
            case R.id.btnJniCallBackStart:
                v.setEnabled(false);
                findViewById(R.id.btnJniCallBackStop).setEnabled(true);
                jni.callBackStart();
                break;
            case R.id.btnJniCallBackStop:
                v.setEnabled(false);
                findViewById(R.id.btnJniCallBackStart).setEnabled(true);
                jni.callBackStop();
                break;
        }
    }
}
