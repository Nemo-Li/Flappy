package com.nemoli.flappy;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;

/**
 * @author : wangli
 * @date : 2020/6/5
 * Email: wangli@znds.com
 */
public class FlappyGlSurfaceView extends GLSurfaceView {

    public FlappyGlSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        try {
            // Create GLES context. Even though we are specifying OpenGL ES 2, it will try to
            // create the highest possible context on a phone
            setEGLContextClientVersion(3);

            // set our custom Renderer for drawing on the created SurfaceView
            FlappyRender flappyRender = new FlappyRender();
            setEGLConfigChooser(8, 8, 8, 8, 16, 8);
            setRenderer(flappyRender);

            // calls onDrawFrame(...) continuously
            setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);

        } catch (Exception e) {
            // Trouble, something's wrong!
            Log.e("MyGLSurfaceView", "Unable to create GLES context!", e);
        }

    }
}
