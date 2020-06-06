#include <jni.h>
#include "Render.h"
#include "TriangleSample.h"

//
// Created by Nemo li on 2020/6/5.
//

Render pRender;
TriangleSample triangleSample;


extern "C"
JNIEXPORT void JNICALL
Java_com_nemoli_flappy_FlappyRender_surfaceChangedNative(JNIEnv *env, jobject thiz, jint width,
                                                         jint height) {
    pRender.setViewport(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nemoli_flappy_FlappyRender_surfaceCreatedNative(JNIEnv *env, jobject thiz) {
    pRender = Render();
    triangleSample = TriangleSample();
    triangleSample.Init();
    pRender.performGLInit();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nemoli_flappy_FlappyRender_drawFrameNative(JNIEnv *env, jobject thiz) {
    triangleSample.Draw();
}
