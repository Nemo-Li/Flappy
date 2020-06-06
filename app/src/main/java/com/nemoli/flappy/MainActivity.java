package com.nemoli.flappy;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;

public class MainActivity extends Activity {

    private native void createObjectNative(AssetManager assetManager, String pathToInternalDir);

    private native void deleteObjectNative();

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
