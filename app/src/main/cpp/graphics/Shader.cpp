//
// Created by Nemo li on 2020/6/6.
//

#include "Shader.h"
#include "../CLogger.h"
#include "../ShaderHelper.h"
#include <fstream>
#include <gtc/type_ptr.hpp>

Shader Shader::BG = Shader();
Shader Shader::BIRD = Shader();
Shader Shader::PIPE = Shader();
Shader Shader::FADE = Shader();
GLuint Shader::id = 0;

void Shader::loadAll() {
//    BG = Shader("shaders/bg.vert", "shaders/bg.frag");
    BIRD = Shader("shaders/bird.vert", "shaders/bird.frag");
//    PIPE = Shader("shaders/pipe.vert", "shaders/pipe.frag");
//    FADE = Shader("shaders/fade.vert", "shaders/fade.frag");
}

Shader::Shader() {

}

Shader::Shader(string vertex, string fragment) {
    string vertexShaderCode;
    if (!readShaderCode(vertexShaderCode, vertex)) {
        CLOGE("Error in reading Vertex shader");
        return;
    }

    string fragmentShaderCode;
    if (!readShaderCode(fragmentShaderCode, fragment)) {
        CLOGE("Error in reading Vertex shader");
        return;
    }

    Shader::id = ShaderHelper::CreateProgram(vertexShaderCode.c_str(), fragmentShaderCode.c_str());
    CLOGD("创建程序id：%d", Shader::id);
}

Shader::~Shader() {

}

/**
 * Read the shader code from assets
 */
bool Shader::readShaderCode(string &shaderCode, string &shaderFileName) {

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

void Shader::enable() {
    glUseProgram(Shader::id);
    CLOGI("glUserProgram %d", Shader::id);
    enabled = true;
}

void Shader::disable() {
    glUseProgram(0);
    enabled = false;
}

int Shader::getUniform(string name) {
    if (locationCache.count(name) == 1) {
        return locationCache[name];
    }
    GLint result = glGetUniformLocation(Shader::id, name.c_str());
    if (result == -1) {
        CLOGD("Could not find uniform variable %s", name.c_str());
    } else {
        locationCache[name] = result;
    }
    return result;
}

void Shader::setUniform1i(string name, int value) {
    if (!enabled) enable();
    glUniform1i(getUniform(name), value);
}

void Shader::setUniform1f(string name, float value) {
    if (!enabled) enable();
    glUniform1f(getUniform(name), value);
}

void Shader::setUniform2f(string name, float x, float y) {
    if (!enabled) enable();
    glUniform2f(getUniform(name), x, y);
}

void Shader::setUniform3f(string name, glm::vec3 vector) {
    if (!enabled) enable();
    glUniform3f(getUniform(name), vector.x, vector.y, vector.z);
}

void Shader::setUniformMat4f(string name, glm::mat4 matrix) {
    if (!enabled) enable();
    glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(matrix));
}
