package com.nemoli.flappy;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;

public class MainActivity extends Activity implements View.OnKeyListener {

    private native void createObjectNative(AssetManager assetManager, String pathToInternalDir);

    private native void deleteObjectNative();

    private native void actionDown(boolean down);

    private View focusView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        AssetManager assetManager = getAssets();
        //File 缓存路径
        String pathToInternalDir = getFilesDir().getAbsolutePath();

        // call the native constructors to create an object
        createObjectNative(assetManager, pathToInternalDir);

        setContentView(R.layout.activity_main);
        focusView = findViewById(R.id.empty_focus_view);
        focusView.requestFocus();
        focusView.setOnKeyListener(this);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (event.getAction() == MotionEvent.ACTION_DOWN) {
            Log.d("wangli", "action_down");
            actionDown(true);
        }
        if (event.getAction() == MotionEvent.ACTION_UP) {
            Log.d("wangli", "action_up");
            actionDown(false);
        }
        return super.onTouchEvent(event);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        // We are exiting the activity, let's delete the native objects
        deleteObjectNative();
    }

    // Used to load the 'libflappy.so' library on application startup.
    static {
        System.loadLibrary("flappy");
    }

    @Override
    public boolean onKey(View v, int keyCode, KeyEvent event) {
        if (event.getAction() == KeyEvent.ACTION_DOWN) {
            actionDown(true);
        } else if (event.getAction() == KeyEvent.ACTION_UP) {
            actionDown(false);
        }
        return false;
    }
}
