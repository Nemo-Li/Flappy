//
// Created by Nemo li on 2020/6/5.
//

#include "BackGround.h"
#include "ShaderHelper.h"
#include "CLogger.h"
#include "stb_image.h"
#include <fstream>

BackGround::BackGround() = default;

BackGround::~BackGround() = default;

void BackGround::Init() {
    string vertexShaderCode;
    string vertexFile = string("shaders/triangle.vert");
    if (!readShaderCode(vertexShaderCode, vertexFile)) {
        CLOGE("Error in reading Vertex shader");
        return;
    }

    string fragmentShaderCode;
    string fragmentFile = string("shaders/triangle.frag");
    if (!readShaderCode(fragmentShaderCode, fragmentFile)) {
        CLOGE("Error in reading Vertex shader");
        return;
    }

    m_ProgramObj = ShaderHelper::CreateProgram(vertexShaderCode.c_str(), fragmentShaderCode.c_str(),
                                               m_VertexShader,
                                               m_FragmentShader);

    GLfloat vertices[] = {
            1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 0.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // create and fill array with texture names in GL
    glGenTextures(1, &textureGLNames);

    // bind the texture
    glBindTexture(GL_TEXTURE_2D, textureGLNames);
    // specify linear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // load the OpenCV Mat into GLES

    unsigned char *image = jniHelper->ExtractAssetImage("res/bg.jpeg");

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, jniHelper->imageW,
                 jniHelper->imageH, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 image);
    stbi_image_free(image);
}

void BackGround::Draw() {
    if (m_ProgramObj == 0) {
        return;
    }
    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glBindTexture(GL_TEXTURE_2D, textureGLNames);

    // Use the program object
    glUseProgram(m_ProgramObj);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void BackGround::Destroy() {
    if (m_ProgramObj) {
        glDeleteProgram(m_ProgramObj);
        m_ProgramObj = GL_NONE;
    }
}

/**
 * Read the shader code from assets
 */
bool BackGround::readShaderCode(string &shaderCode, string &shaderFileName) {

    CLOGI("Reading shader: %s", shaderFileName.c_str());

    // android shaders are stored in assets
    // read them using MyJNIHelper
    bool isFilePresent = jniHelper->ExtractAssetReturnFilename(shaderFileName,
                                                               shaderFileName);
    if (!isFilePresent) {
        return false;
    }

    ifstream shaderStream(shaderFileName.c_str(), ios::in);
    if (shaderStream.is_open()) {
        std::string Line;
        while (getline(shaderStream, Line)) {
            shaderCode += "\n" + Line;
        }
        CLOGD("%s", shaderCode.c_str());
        shaderStream.close();
    } else {
        CLOGF("Cannot open %s", shaderFileName.c_str());
        return false;
    }
    CLOGI("Read successfully");
    return true;
}