//
// Created by Nemo li on 2020/6/6.
//

#include "Bird.h"
#include "gtc/matrix_transform.hpp"
#include "../CLogger.h"
#include "../input/Input.h"

Bird::Bird() {
    float vertices[] = {
            -size / 2.0f, -size / 2.0f, 0.0f,
            -size / 2.0f, size / 2.0f, 0.0f,
            size / 2.0f, size / 2.0f, 0.0f,
            size / 2.0f, -size / 2.0f, 0.0f
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

    texture = new Texture("bird.png", true);
    mesh = new VertexArray(vertices, indices, tcs, sizeof(vertices), sizeof(indices), sizeof(tcs));
}

Bird::~Bird() = default;

void Bird::update() {
    position.y -= delta;
    CLOGD("actionDown大小为 %d", actionDown);
    if (actionDown == 1) {
        delta += -0.001f;
    } else {
        delta += 0.001f;
    }
    rot = -delta * 90.0f;
}

void Bird::fall() {
    delta = -0.15f;
}

void Bird::render() {
//    CLOGD("render");

    Shader::BIRD.enable();
//    CLOGD("BIRD.enable()");
    glm::mat4 trans = glm::mat4(1.0f);
    Shader::BIRD.setUniformMat4f("vw_matrix", trans);

//    trans = glm::matrixCompMult(glm::translate(trans, position),
//                                glm::rotate(trans, glm::radians(rot), glm::vec3(0.0, 0.0, 1.0)));

    trans = glm::translate(trans, position);
    trans = glm::rotate(trans, glm::radians(rot), glm::vec3(0.0, 0.0, 1.0));
    Shader::BIRD.setUniformMat4f("ml_matrix", trans);

    texture->bind();
    mesh->render();
    Shader::BIRD.disable();
}

float Bird::getY() {
    return position.y;
}

float Bird::getSize() {
    return size;
}


