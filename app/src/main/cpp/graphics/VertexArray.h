//
// Created by Nemo li on 2020/6/6.
//

#ifndef FLAPPY_VERTEXARRAY_H
#define FLAPPY_VERTEXARRAY_H
#include "GLES3/gl32.h"


class VertexArray {
private:
    GLuint vao, vbo, ibo, tbo;
    int count;
public:
    VertexArray(int count);

    VertexArray(float vertices[], int indices[], float textureCoordinates[]);

    void bind();

    void unbind();

    void draw();

    void render();
};


#endif //FLAPPY_VERTEXARRAY_H
