//
// Created by Nemo li on 2020/6/5.
//

#ifndef FLAPPY_SHADERHELPER_H
#define FLAPPY_SHADERHELPER_H

#include <GLES3/gl32.h>
#include <string>
#include "glm/glm.hpp"

using namespace std;

class ShaderHelper {
public:
    static GLuint LoadShader(GLenum shaderType, const char *pSource);

    static GLuint CreateProgram(const char *pVertexShaderSource, const char *pFragShaderSource,
                                GLuint &vertexShaderHandle,
                                GLuint &fragShaderHandle);

    static GLuint CreateProgram(const char *pVertexShaderSource, const char *pFragShaderSource);

    static GLuint CreateProgramWithFeedback(const char *pVertexShaderSource, const char *pFragShaderSource,
                              GLuint &vertexShaderHandle,
                              GLuint &fragShaderHandle, const GLchar **varying, int varyingCount);

    static void DeleteProgram(GLuint &program);

    static void CheckGLError(const char *pGLOperation);

    // utility uniform functions
    // ------------------------------------------------------------------------
    static void setBool(GLuint programId, const string &name, bool value) {
        glUniform1i(glGetUniformLocation(programId, name.c_str()), (int) value);
    }

    // ------------------------------------------------------------------------
    static void setInt(GLuint programId, const string &name, int value) {
        glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
    }

    // ------------------------------------------------------------------------
    static void setFloat(GLuint programId, const string &name, float value) {
        glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
    }

    // ------------------------------------------------------------------------
    static void setVec2(GLuint programId, const string &name, const glm::vec2 &value) {
        glUniform2fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
    }

    static void setVec2(GLuint programId, const string &name, float x, float y) {
        glUniform2f(glGetUniformLocation(programId, name.c_str()), x, y);
    }

    // ------------------------------------------------------------------------
    static void setVec3(GLuint programId, const string &name, const glm::vec3 &value) {
        glUniform3fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
    }

    static void setVec3(GLuint programId, const string &name, float x, float y, float z) {
        glUniform3f(glGetUniformLocation(programId, name.c_str()), x, y, z);
    }

    // ------------------------------------------------------------------------
    static void setVec4(GLuint programId, const string &name, const glm::vec4 &value) {
        glUniform4fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
    }

    static void setVec4(GLuint programId, const string &name, float x, float y, float z, float w) {
        glUniform4f(glGetUniformLocation(programId, name.c_str()), x, y, z, w);
    }

    // ------------------------------------------------------------------------
    static void setMat2(GLuint programId, const string &name, const glm::mat2 &mat) {
        glUniformMatrix2fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    // ------------------------------------------------------------------------
    static void setMat3(GLuint programId, const string &name, const glm::mat3 &mat) {
        glUniformMatrix3fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    // ------------------------------------------------------------------------
    static void setMat4(GLuint programId, const string &name, const glm::mat4 &mat) {
        glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
};

#endif //FLAPPY_SHADERHELPER_H
