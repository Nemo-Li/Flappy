//
// Created by Nemo li on 2020/6/6.
//

#include "Pipe.h"
#include "gtc/matrix_transform.hpp"

float Pipe::width = 1.5f, Pipe::height = 8.0f;
Texture *Pipe::texture = nullptr;
VertexArray *Pipe::mesh = nullptr;


Pipe::Pipe() {
}

Pipe::~Pipe() {

}

void Pipe::create() {
    float vertices[] = {
            0.0f, 0.0f, 0.1f,
            0.0f, height, 0.1f,
            width, height, 0.1f,
            width, 0.0f, 0.1f
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    float tcs[] = {
            0, 1,
            0, 0,
            1, 0,
            1, 1
    };

    mesh = new VertexArray(vertices, indices, tcs, sizeof(vertices), sizeof(indices), sizeof(tcs));
    texture = new Texture("pipe.png", true);
}

Pipe::Pipe(float x, float y) {
    position.x = x;
    position.y = y;

    glm::mat4 tran = glm::mat4(1.0f);
    ml_matrix = glm::translate(tran, position);
}

float Pipe::getX() {
    return position.x;
}

float Pipe::getY() {
    return position.y;
}

glm::mat4 Pipe::getModelMatrix() {
    return ml_matrix;
}

VertexArray Pipe::getMesh() {
    return *mesh;
}

Texture Pipe::getTexture() {
    return *texture;
}

float Pipe::getWidth() {
    return width;
}

float Pipe::getHeight() {
    return height;
}
