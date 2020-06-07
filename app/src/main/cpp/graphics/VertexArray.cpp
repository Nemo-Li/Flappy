//
// Created by Nemo li on 2020/6/6.
//

#include <GLES3/gl32.h>
#include "VertexArray.h"
#include "Shader.h"

VertexArray::VertexArray(int count) {
    VertexArray::count = count;
    glGenVertexArrays(1, &vao);
}

VertexArray::VertexArray(float *vertices, int *indices, float *textureCoordinates) {

    count = sizeof(&indices) / sizeof(indices[0]);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(Shader::VERTEX_ATTRIB, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(Shader::VERTEX_ATTRIB);

    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates), textureCoordinates, GL_STATIC_DRAW);
    glVertexAttribPointer(Shader::TCOORD_ATTRIB, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(Shader::TCOORD_ATTRIB);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VertexArray::bind() {
    glBindVertexArray(vao);
    if (ibo > 0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
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
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_BYTE, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, count);
    }
}

void VertexArray::render() {
    bind();
    draw();
}

VertexArray::VertexArray() {

}

