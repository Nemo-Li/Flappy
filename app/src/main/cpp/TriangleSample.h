//
// Created by Nemo li on 2020/6/5.
//

#ifndef FLAPPY_TRIANGLESAMPLE_H
#define FLAPPY_TRIANGLESAMPLE_H

#include <GLES3/gl32.h>
#include "JNIHelper.h"

class TriangleSample {
public:
    TriangleSample();

    virtual ~TriangleSample();

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

#endif //FLAPPY_TRIANGLESAMPLE_H
