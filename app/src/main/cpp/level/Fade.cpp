//
// Created by Nemo li on 2020/6/10.
//

#include "Fade.h"
#include "../graphics/VertexArray.h"
#include "../graphics/Shader.h"

Fade::Fade() {
    float vertices[] = {
            -1.0, -1.0, -0.5,
            -1.0, 1.0, 0.5,
            1.0, 1.0, -0.5,
            1.0, -1.0, -0.5
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

}

Fade::~Fade() {

}

void Fade::render(int time) {
    Shader::FADE.enable();
    Shader::FADE.setUniform1f("time", time);
    Shader::FADE.disable();
}

