package com.nemoli.flappy;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * @author : wangli
 * @date : 2020/6/5
 * Email: wangli@znds.com
 */
public class FlappyRender implements GLSurfaceView.Renderer {

    private native void drawFrameNative();

    private native void surfaceCreatedNative();

    private native void surfaceChangedNative(int width, int height);

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        surfaceCreatedNative();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        surfaceChangedNative(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        drawFrameNative();
    }
}
