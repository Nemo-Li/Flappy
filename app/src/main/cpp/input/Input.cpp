#include <jni.h>
#include "Input.h"
#include "../CLogger.h"
//
// Created by Nemo li on 2020/6/6.
//
extern "C"
JNIEXPORT void JNICALL
Java_com_nemoli_flappy_MainActivity_actionDown(JNIEnv *env, jobject thiz, jboolean down) {
    actionDown = down;
    CLOGD("屏幕点击%u", down);
}
