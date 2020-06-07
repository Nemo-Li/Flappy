package com.nemoli.flappy;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.view.MotionEvent;

public class MainActivity extends Activity {

    private native void createObjectNative(AssetManager assetManager, String pathToInternalDir);

    private native void deleteObjectNative();

    private native void actionDown(boolean down);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        AssetManager assetManager = getAssets();
        //File 缓存路径
        String pathToInternalDir = getFilesDir().getAbsolutePath();

        // call the native constructors to create an object
        createObjectNative(assetManager, pathToInternalDir);

        setContentView(R.layout.activity_main);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (event.getAction() == MotionEvent.ACTION_DOWN) {
            actionDown(true);
        }
        if (event.getAction() == MotionEvent.ACTION_UP) {
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
}
