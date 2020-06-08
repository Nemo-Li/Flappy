//
// Created by Nemo li on 2020/6/6.
//

#ifndef FLAPPY_SHADER_H
#define FLAPPY_SHADER_H

#include <string>
#include "../JNIHelper.h"
#include <map>
#include "glm.hpp"
#include "GLES3/gl32.h"

using namespace std;

class Shader {
public:
    const static int VERTEX_ATTRIB = 0;
    const static int TCOORD_ATTRIB = 1;

    static Shader BG, BIRD, PIPE, FADE;

    static void loadAllPath();

    static void loadAllString();

    Shader();

    Shader(string vertex, string fragment);

    Shader(string vertexCode, string fragmentCode, bool code);

    virtual ~Shader();

    bool readShaderCode(string &shaderCode, string &shaderFileName);

    void enable();

    void disable();

    int getUniform(string name);

    void setUniform1i(string name, int value);

    void setUniform1f(string name, float value);

    void setUniform2f(string name, float x, float y);

    void setUniform3f(string name, glm::vec3 vector);

    void setUniformMat4f(string name, glm::mat4 matrix);

private:
    bool enabled = false;
    GLuint id;
    map<string, int> locationCache;
};

extern JNIHelper *jniHelper;

#endif //FLAPPY_SHADER_H
