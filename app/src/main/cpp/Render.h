//
// Created by Nemo li on 2020/6/5.
//

#ifndef FLAPPY_RENDER_H
#define FLAPPY_RENDER_H

#include <string>
#include <GLES3/gl32.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include "CLogger.h"
#include "JNIHelper.h"
#include "level/Bird.h"

using namespace std;

class Render {
public:
    Render();

    virtual ~Render();

    void performGLInit();

    void setViewport(int width, int height);

    void checkGLError(string funcName);

    void render();

private:
    Bird *bird;
};

extern JNIHelper *jniHelper;


#endif //FLAPPY_RENDER_H
