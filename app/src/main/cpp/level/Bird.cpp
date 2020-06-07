//
// Created by Nemo li on 2020/6/6.
//

#include "Bird.h"
#include "gtc/matrix_transform.hpp"
#include "../CLogger.h"

Bird::Bird() {
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 1.0f
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

//    int num = sizeof(indices) / sizeof(indices[0]);
//    CLOGD("数组长度 %d", num);

    texture = new Texture("bg.jpeg");
    mesh = new VertexArray(vertices, indices, tcs, sizeof(vertices), sizeof(indices), sizeof(tcs));
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
    CLOGD("render");

    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

    Shader::BIRD.enable();
    CLOGD("BIRD.enable()");
//    glm::mat4 trans = glm::mat4(1.0f);
//    Shader::BIRD.setUniformMat4f("vw_matrix", trans);
//    CLOGD("setUniformMat4f");

//    trans = glm::matrixCompMult(glm::translate(trans, position),
//                                glm::rotate(trans, glm::radians(rot), glm::vec3(0.0, 0.0, 1.0)));
//    Shader::BIRD.setUniformMat4f("ml_matrix", trans);
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


