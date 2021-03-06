//
// Created by Nemo li on 2020/6/5.
//

#define STB_IMAGE_IMPLEMENTATION

#include "JNIHelper.h"
#include <android/asset_manager_jni.h>
#include "CLogger.h"
#include "stb_image.h"

JNIHelper::JNIHelper(JNIEnv *env, jobject obj, jobject assetManager, jstring pathToInternalDir) {
    // get a native instance of the asset manager
    // assetManager is passed from Java and should not be garbage collected!
    apkAssetManager = AAssetManager_fromJava(env, assetManager);

    //Save app internal data storage path -- we will extract assets and save here
    const char *cPathToInternalDir;
    cPathToInternalDir = env->GetStringUTFChars(pathToInternalDir, nullptr);

    apkInternalPath = string(cPathToInternalDir);
    env->ReleaseStringUTFChars(pathToInternalDir, cPathToInternalDir);

    //mutex for thread safety
    pthread_mutex_init(&threadMutex, nullptr);
}

JNIHelper::~JNIHelper() {
    pthread_mutex_destroy(&threadMutex);
}

/**
 * Search for a file in assets, extract it, save it in internal storage, and return the new path
 */
bool JNIHelper::ExtractAssetReturnFilename(string assetName, string &filename,
                                           bool checkIfFileIsAvailable) {

    // construct the filename in internal storage by concatenating with path to internal storage
    filename = apkInternalPath + "/" + getFileName(assetName);

    // check if the file was previously extracted and is available in app's internal dir
    FILE *file = fopen(filename.c_str(), "rb");
    if (file && checkIfFileIsAvailable) {
        CLOGI("Found extracted file in assets: %s", filename.c_str());
        fclose(file);
        pthread_mutex_unlock(&threadMutex);
        return true;
    }

    // let us look for the file in assets
    bool result = false;

    // AAsset objects are not thread safe and need to be protected with mutex
    pthread_mutex_lock(&threadMutex);

    // Open file
    AAsset *asset = AAssetManager_open(apkAssetManager, assetName.c_str(), AASSET_MODE_STREAMING);

    char buf[BUFSIZ];
    int nb_read = 0;
    if (asset != nullptr) {
        FILE *out = fopen(filename.c_str(), "w");
        while ((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0) {
            fwrite(buf, nb_read, 1, out);
        }
        fclose(out);
        AAsset_close(asset);
        result = true;

        CLOGI("Asset extracted: %s", filename.c_str());
    } else {
        CLOGE("Asset not found: %s", assetName.c_str());
    }

    pthread_mutex_unlock(&threadMutex);
    return result;
}


string JNIHelper::getFileName(string fileName) {
    // assume filename is of the form "<path>/<name>.<type>"
    string::size_type slashIndex = fileName.find_last_of('/');

    string onlyName;
    if (slashIndex == string::npos) {
        onlyName = fileName.substr(0, string::npos);
    } else {
        onlyName = fileName.substr(slashIndex + 1, string::npos);
    }

    return onlyName;
}

unsigned char *JNIHelper::ExtractAssetImage(string assetName) {
    int n;
    CLOGD("加载图片%s", assetName.c_str());
    // Open file
    AAsset *asset = AAssetManager_open(apkAssetManager, assetName.c_str(), AASSET_MODE_STREAMING);
    off_t assetLength = AAsset_getLength(asset);
    auto *fileData = (unsigned char *) AAsset_getBuffer(asset);
    unsigned char *image = stbi_load_from_memory(fileData, assetLength, &imageW, &imageH, &n, 0);
    return image;
}
