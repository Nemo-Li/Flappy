//
// Created by Nemo li on 2020/6/6.
//

#ifndef FLAPPY_VERTEXARRAY_H
#define FLAPPY_VERTEXARRAY_H
#include "GLES3/gl32.h"


class VertexArray {
private:
    GLuint vao, vbo, ibo, tbo;
public:
    int count = 0;

    VertexArray();

    VertexArray(int count);

    VertexArray(float vertices[], unsigned int indices[], float textureCoordinates[], int vLength, int iLength, int tLength);

    void bind();

    void unbind();

    void draw();

    void render();
};


#endif //FLAPPY_VERTEXARRAY_H
