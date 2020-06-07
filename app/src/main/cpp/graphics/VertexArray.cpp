//
// Created by Nemo li on 2020/6/6.
//

#include <GLES3/gl32.h>
#include "VertexArray.h"
#include "Shader.h"
#include "../CLogger.h"

VertexArray::VertexArray(int count) {
    VertexArray::count = count;
    glGenVertexArrays(1, &vao);
}

VertexArray::VertexArray(float *vertices, int *indices, float *textureCoordinates, int vLength,
                         int iLength, int tLength) {
    CLOGD("VertexArray方法");
    VertexArray::count = iLength;
    CLOGD("赋值后count %d", count);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vLength, vertices, GL_STATIC_DRAW);

    CLOGD("VERTEX_ATTRIB前");
    glVertexAttribPointer(Shader::VERTEX_ATTRIB, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(Shader::VERTEX_ATTRIB);
    CLOGD("VERTEX_ATTRIB后");

    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, tLength, textureCoordinates, GL_STATIC_DRAW);
    glVertexAttribPointer(Shader::TCOORD_ATTRIB, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(Shader::TCOORD_ATTRIB);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iLength, indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    CLOGD("结束");
}

void VertexArray::bind() {
    glBindVertexArray(vao);
    if (ibo > 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        CLOGD("VertexArray::bind()");
    }
}

void VertexArray::unbind() {
    if (ibo > 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);
}

void VertexArray::draw() {
    if (ibo > 0) {
        CLOGD(" VertexArray::draw ibo %d", ibo);
        CLOGD(" VertexArray::draw count %d", count);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_BYTE, 0);
    } else {
        CLOGD("VertexArray::bind() coung %d", count);
        glDrawArrays(GL_TRIANGLES, 0, count);
    }
}

void VertexArray::render() {
    bind();
    draw();
}

VertexArray::VertexArray() {

}

