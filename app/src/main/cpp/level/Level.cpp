//
// Created by Nemo li on 2020/6/6.
//

#include "Level.h"
#include "gtc/matrix_transform.hpp"

Level::Level() {
//    float vertices[] = {
//            -10.0f, -10.0f * 9.0f / 16.0f, 0.0f,
//            -10.0f, 10.0f * 9.0f / 16.0f, 0.0f,
//            0.0f, 10.0f * 9.0f / 16.0f, 0.0f,
//            0.0f, -10.0f * 9.0f / 16.0f, 0.0f
//    };

    float vertices[] = {
            -1.0f, -1.0f, 0.0f,
            -1.0, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
            1.0f, -1.0f, 0.0f
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

//    fade = VertexArray(6);
    background = VertexArray(vertices, indices, tcs, sizeof(vertices), sizeof(indices),
                             sizeof(tcs));
    bgTexture = Texture("bg.jpeg", false);
    bird = Bird();

//    createPipes();
}


void Level::render() {
    bgTexture.bind();
    Shader::BG.enable();
    Shader::BG.setUniform2f("bird", 0, bird.getY());
    background.bind();
    background.draw();

//    for (int i = map; i < map + 4; i++) {
//        glm::mat4 trans = glm::mat4(1.0f);
//        Shader::BG.setUniformMat4f("vw_matrix",
//                                   glm::translate(trans,
//                                                  glm::vec3(i * 10 + xScroll * 0.03f, 0.0f, 0.0f)));
//        background.draw();
//    }
    Shader::BG.disable();
    bgTexture.unbind();

//    renderPipes();
    bird.render();

//    Shader::FADE.enable();
//    Shader::FADE.setUniform1f("time", time);
//    fade.render();
//    Shader::FADE.disable();
}

Level::~Level() {

}

