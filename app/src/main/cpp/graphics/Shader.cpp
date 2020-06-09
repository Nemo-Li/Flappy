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

void Shader::loadAllString() {
    string bgVert = "#version 310 es\n"
                    "#extension GL_EXT_shader_io_blocks : enable\n"
                    "\n"
                    "layout (location = 0) in vec4 position;\n"
                    "layout (location = 1) in vec2 tc;\n"
                    "\n"
                    "uniform mat4 pr_matrix;\n"
                    "uniform mat4 vw_matrix;\n"
                    "\n"
                    "out DATA\n"
                    "{\n"
                    "vec2 tc;\n"
                    "vec3 position;\n"
                    "} vs_out;\n"
                    "\n"
                    "void main()\n"
                    "{\n"
                    "gl_Position = pr_matrix * vw_matrix * position;\n"
                    "vs_out.tc = tc;\n"
                    "vs_out.position = vec3(vw_matrix * position);\n"
                    "}";

    string bgFrag = "#version 310 es\n"
                    "#extension GL_EXT_shader_io_blocks : enable\n"
                    "precision mediump float;\n"
                    "\n"
                    "layout (location = 0) out vec4 color;\n"
                    "\n"
                    "in DATA\n"
                    "{\n"
                    "vec2 tc;\n"
                    "vec3 position;\n"
                    "} fs_in;\n"
                    "\n"
                    "uniform vec2 bird;\n"
                    "uniform sampler2D tex;\n"
                    "\n"
                    "void main()\n"
                    "{\n"
                    "color = texture(tex, fs_in.tc);\n"
                    "color *= 2.0 / (length(bird - fs_in.position.xy) + 2.5) + 0.5;\n"
                    "}";
    BG = Shader(bgVert, bgFrag, true);

    string birdVert = "#version 310 es\n"
                      "#extension GL_EXT_shader_io_blocks : enable\n"
                      "\n"
                      "layout (location = 0) in vec4 position;\n"
                      "layout (location = 1) in vec2 tc;\n"
                      "\n"
                      "out DATA\n"
                      "{\n"
                      "vec2 tc;\n"
                      "} vs_out;\n"
                      "\n"
                      "uniform mat4 pr_matrix;\n"
                      "uniform mat4 vw_matrix;\n"
                      "uniform mat4 ml_matrix;\n"
                      "\n"
                      "void main()\n"
                      "{\n"
                      "gl_Position = pr_matrix * vw_matrix * ml_matrix * position;\n"
                      "vs_out.tc = tc;\n"
                      "}";

    string birdFrag = "#version 310 es\n"
                      "#extension GL_EXT_shader_io_blocks : enable\n"
                      "precision mediump float;\n"
                      "\n"
                      "layout (location = 0) out vec4 color;\n"
                      "\n"
                      "in DATA\n"
                      "{\n"
                      "vec2 tc;\n"
                      "} fs_in;\n"
                      "\n"
                      "uniform sampler2D tex;\n"
                      "\n"
                      "void main()\n"
                      "{\n"
                      "color = texture(tex, fs_in.tc);\n"
                      "if (color.w < 1.0)\n"
                      "discard;\n"
                      "}";

    BIRD = Shader(birdVert, birdFrag, true);

    string pipeVert = "#version 310 es\n"
                      "#extension GL_EXT_shader_io_blocks : enable\n"
                      "\n"
                      "layout (location = 0) in vec4 position;\n"
                      "layout (location = 1) in vec2 tc;\n"
                      "\n"
                      "uniform mat4 pr_matrix;\n"
                      "uniform mat4 vw_matrix;\n"
                      "uniform mat4 ml_matrix;\n"
                      "\n"
                      "out DATA\n"
                      "{\n"
                      "    vec2 tc;\n"
                      "    vec3 position;\n"
                      "} vs_out;\n"
                      "\n"
                      "void main()\n"
                      "{\n"
                      "    gl_Position = pr_matrix * vw_matrix * ml_matrix * position;\n"
                      "    vs_out.tc = tc;\n"
                      "    vs_out.position = vec3(vw_matrix * ml_matrix * position);\n"
                      "}";
    string pipeFrag = "#version 310 es\n"
                      "#extension GL_EXT_shader_io_blocks : enable\n"
                      "precision mediump float;\n"
                      "\n"
                      "layout (location = 0) out vec4 color;\n"
                      "\n"
                      "in DATA\n"
                      "{\n"
                      "vec2 tc;\n"
                      "vec3 position;\n"
                      "} fs_in;\n"
                      "\n"
                      "uniform vec2 bird;\n"
                      "uniform sampler2D tex;\n"
                      "uniform int top;\n"
                      "\n"
                      "void main()\n"
                      "{\n"
                      "vec2 tc = fs_in.tc;\n"
                      "if (top == 1)\n"
                      "tc.y = 1.0 - tc.y;\n"
                      "\n"
                      "color = texture(tex, fs_in.tc);\n"
                      "if (color.w < 1.0)\n"
                      "discard;\n"
                      "color *= 2.0 / (length(bird - fs_in.position.xy) + 1.5) + 0.5;\n"
                      "color.w = 1.0;\n"
                      "}";
    PIPE = Shader(pipeVert, pipeFrag, true);

    string fadeVert = "#version 310 es\n"
                      "\n"
                      "void main()\n"
                      "{\n"
                      "const vec4 vertices[6] = vec4[6](vec4( 1.0, -1.0, -0.5, 1.0),\n"
                      " vec4(-1.0, -1.0, -0.5, 1.0),\n"
                      " vec4( 1.0,  1.0, -0.5, 1.0),\n"
                      " vec4( 1.0,  1.0, -0.5, 1.0),\n"
                      " vec4(-1.0, -1.0, -0.5, 1.0),\n"
                      " vec4(-1.0,  1.0, -0.5, 1.0));\n"
                      "gl_Position = vertices[gl_VertexID];\n"
                      "}";
    string fadeFrag = "#version 310 es\n"
                      "precision mediump float;\n"
                      "\n"
                      "layout (location = 0) out vec4 color;\n"
                      "\n"
                      "uniform float time;\n"
                      "\n"
                      "void main()\n"
                      "{\n"
                      "if (time > 1.0)\n"
                      "discard;\n"
                      "color = vec4(1.0, 1.0, 1.0, 1.0 - time);\n"
                      "}";
    FADE = Shader(fadeVert, fadeFrag, true);
}

void Shader::loadAllPath() {
    PIPE = Shader("shaders/pipe.vert", "shaders/pipe.frag");
    BG = Shader("shaders/bg.vert", "shaders/bg.frag");
    BIRD = Shader("shaders/bird.vert", "shaders/bird.frag");
    FADE = Shader("shaders/fade.vert", "shaders/fade.frag");
}

Shader::Shader() {

}

Shader::Shader(string vertexCode, string fragmentCode, bool code) {
    Shader::id = ShaderHelper::CreateProgram(vertexCode.c_str(), fragmentCode.c_str());
    CLOGD("创建程序id：%d", Shader::id);
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

