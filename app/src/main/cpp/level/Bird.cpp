//
// Created by Nemo li on 2020/6/6.
//

#include "Bird.h"
#include "gtc/matrix_transform.hpp"

Bird::Bird() {
    float vertices[] = {
            -size / 2.0f, -size / 2.0f, 0.2f,
            -size / 2.0f, size / 2.0f, 0.2f,
            size / 2.0f, size / 2.0f, 0.2f,
            size / 2.0f, -size / 2.0f, 0.2f
    };

    int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    float tcs[] = {
            0, 1,
            0, 0,
            1, 0,
            1, 1
    };

    Bird::texture = Texture("bird.png");
    mesh = VertexArray(vertices, indices, tcs);
}

Bird::~Bird() = default;

void Bird::update() {
//    position.y -= delta;
//    if (actionDown) {
//        delta = -0.15;
//    } else {
//        delta += 0.01f;
//    }
//    rot = -delta * 90.0f;
}

void Bird::fall() {
    delta = -0.15f;
}

void Bird::render() {
    Shader::BIRD.enable();
    glm::mat4 trans = glm::mat4(1.0f);
    Shader::BIRD.setUniformMat4f("vw_matrix", trans);

    trans = glm::matrixCompMult(glm::translate(trans, position),
                                glm::rotate(trans, glm::radians(rot), glm::vec3(0.0, 0.0, 1.0)));
    Shader::BIRD.setUniformMat4f("ml_matrix", trans);
    texture.bind();
    mesh.render();
    Shader::BIRD.disable();
}

float Bird::getY() {
    return position.y;
}

float Bird::getSize() {
    return size;
}


