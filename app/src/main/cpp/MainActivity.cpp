#include <jni.h>
#include "JNIHelper.h"

//
// Created by Nemo li on 2020/6/5.
//

JNIHelper *jniHelper = nullptr;

extern "C"
JNIEXPORT void JNICALL
Java_com_nemoli_flappy_MainActivity_createObjectNative(JNIEnv *env, jobject thiz,
                                                       jobject asset_manager,
                                                       jstring path_to_internal_dir) {
    jniHelper = new JNIHelper(env, thiz, asset_manager, path_to_internal_dir);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nemoli_flappy_MainActivity_deleteObjectNative(JNIEnv *env, jobject thiz) {
    delete jniHelper;
}
