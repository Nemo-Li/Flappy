//
// Created by Nemo li on 2020/6/5.
//

#ifndef FLAPPY_BACKGROUND_H
#define FLAPPY_BACKGROUND_H

#include <GLES3/gl32.h>
#include "JNIHelper.h"

class BackGround {
public:
    BackGround();

    virtual ~BackGround();

    virtual void Init();

    virtual void Draw();

    virtual void Destroy();

    bool readShaderCode(string &shaderCode, string &shaderFileName);

protected:
    GLuint m_ProgramObj;
    GLuint m_VertexShader;
    GLuint m_FragmentShader;
    GLuint textureGLNames;
    GLuint VBO;
};

extern JNIHelper *jniHelper;

#endif //FLAPPY_BACKGROUND_H
