#include <jni.h>
#include "Render.h"
#include "BackGround.h"

//
// Created by Nemo li on 2020/6/5.
//

Render pRender;
BackGround backGround;


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
    backGround = BackGround();
    backGround.Init();
    pRender.performGLInit();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nemoli_flappy_FlappyRender_drawFrameNative(JNIEnv *env, jobject thiz) {
    backGround.Draw();
}
