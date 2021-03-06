//
// Created by Nemo li on 2020/6/5.
//

#include "Render.h"
#include "gtc/matrix_transform.hpp"
#include "graphics/Shader.h"
#include "level/Bird.h"

Render::Render() {

}

Render::~Render() {

}

void Render::performGLInit() {
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    // glDepthFunc(GL_LEQUAL);
    CLOGI("OpenGL %s, GLSL %s", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

    // check if the device supports GLES 3 or GLES 2
    const char *versionStr = (const char *) glGetString(GL_VERSION);
    if (strstr(versionStr, "OpenGL ES 3.")) {
        CLOGD("Device supports GLES 3");
    } else {
        CLOGD("Device supports GLES 2");
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader::loadAllString();

    glm::mat4 pr_matrix = glm::ortho(-10.0f, 10.0f, -10.0f * 9.0f / 16.0f, 10.0f * 9.0f / 16.0f,
                                     -1.0f, 1.0f);

    Shader::PIPE.setUniformMat4f("pr_matrix", pr_matrix);

    Shader::BIRD.setUniformMat4f("pr_matrix", pr_matrix);

    Shader::BG.setUniformMat4f("pr_matrix", pr_matrix);


    level = new Level();
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

void Render::render() {
    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    level->update();
    if (level->isGameOver()) {
        level = new Level();
    }
    level->render();
}

