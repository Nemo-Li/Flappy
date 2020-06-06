//
// Created by Nemo li on 2020/6/5.
//

#include "Render.h"

Render::Render() {

}

Render::~Render() {

}

void Render::performGLInit() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    CLOGD("GLInit, clear color");

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LEQUAL);

    CLOGI("OpenGL %s, GLSL %s", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

    // check if the device supports GLES 3 or GLES 2
    const char *versionStr = (const char *) glGetString(GL_VERSION);
    if (strstr(versionStr, "OpenGL ES 3.")) {
        CLOGD("Device supports GLES 3");
    } else {
        CLOGD("Device supports GLES 2");
    }

    string shaderFile;
    jniHelper->ExtractAssetReturnFilename("shaders/bg.frag", shaderFile);

    checkGLError("MyGLInit");
}

void Render::checkGLError(string funcName) {
    GLenum err = glGetError();
    if (err == GL_NO_ERROR) {
        return;
    } else {
        CLOGF("[FAIL GL] %s", funcName.c_str());
    }
    switch (err) {

        case GL_INVALID_ENUM:
            CLOGE("GL_INVALID_ENUM: GLenum argument out of range");
            break;

        case GL_INVALID_VALUE:
            CLOGE("GL_INVALID_VALUE: numeric argument out of range");
            break;

        case GL_INVALID_OPERATION:
            CLOGE("GL_INVALID_OPERATION: operation illegal in current state");
            break;

        case GL_INVALID_FRAMEBUFFER_OPERATION:
            CLOGE("GL_INVALID_FRAMEBUFFER_OPERATION: framebuffer object is not complete");
            break;

        case GL_OUT_OF_MEMORY:
            CLOGE("GL_OUT_OF_MEMORY: not enough memory left to execute command");
            break;

        default:
            CLOGE("unlisted error");
            break;
    }

}

void Render::setViewport(int width, int height) {
    glViewport(0, 0, width, height);
    checkGLError("Cube::SetViewport");
}

