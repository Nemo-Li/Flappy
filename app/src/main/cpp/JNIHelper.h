//
// Created by Nemo li on 2020/6/5.
//

#ifndef FLAPPY_JNIHELPER_H
#define FLAPPY_JNIHELPER_H

#include <jni.h>
#include <android/asset_manager.h>
#include <string>
#include <pthread.h>

using namespace std;

class JNIHelper {

private:
    mutable pthread_mutex_t threadMutex;
    string apkInternalPath;
    AAssetManager *apkAssetManager;

public:
    int imageW;

    int imageH;

    JNIHelper(JNIEnv *env, jobject obj, jobject assetManager, jstring pathToInternalDir);

    virtual ~JNIHelper();

    bool ExtractAssetReturnFilename(string assetName, string &filename,
                                    bool checkIfFileIsAvailable = false);

    string getFileName(string fileName);

    unsigned char *ExtractAssetImage(string assetName);
};


#endif //FLAPPY_JNIHELPER_H
