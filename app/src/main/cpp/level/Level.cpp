//
// Created by Nemo li on 2020/6/6.
//

#include "Level.h"
#include "gtc/matrix_transform.hpp"
#include "../input/Input.h"
#include "../CLogger.h"

Level::Level() {
    float vertices[] = {
            -10.0f, -10.0f * 9.0f / 16.0f, 0.0f,
            -10.0f, 10.0f * 9.0f / 16.0f, 0.0f,
            0.0f, 10.0f * 9.0f / 16.0f, 0.0f,
            0.0f, -10.0f * 9.0f / 16.0f, 0.0f
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

    background = VertexArray(vertices, indices, tcs, sizeof(vertices), sizeof(indices),
                             sizeof(tcs));
    bgTexture = Texture("bg.jpeg", false);
    bird = Bird();
    fade = Fade();

    createPipes();
}


void Level::render() {
    renderPipes();
    bgTexture.bind();
    Shader::BG.enable();
    Shader::BG.setUniform2f("bird", 0, bird.getY());
    background.bind();

    for (int i = map; i < map + 4; i++) {
        glm::mat4 trans = glm::mat4(1.0f);
        Shader::BG.setUniformMat4f("vw_matrix",
                                   glm::translate(trans,
                                                  glm::vec3(i * 10.0 + xScroll * 0.03, 0.0f,
                                                            0.0f)));
        background.draw();
    }

    Shader::BG.disable();
    bgTexture.unbind();

    bird.render();
    fade.render(time);

}

Level::~Level() {

}

void Level::update() {
    if (control) {
        xScroll--;
        if (-xScroll % 335 == 0) map++;
        if (-xScroll > 250 && -xScroll % 120 == 0)
            updatePipes();
    }
    bird.update();

    if (control && collision()) {
        bird.fall();
        control = false;
    }

    if (!control && actionDown) {
        reset = true;
    }
    time += 0.01f;
}

void Level::createPipes() {
    Pipe::create();
    for (int i = 0; i < 5 * 2; i += 2) {
        double rand1 = rand() / double(RAND_MAX);
        pipes[i] = Pipe(OFFSET + index * 3.0f, rand1 * 4.0f);
        pipes[i + 1] = Pipe(pipes[i].getX(), pipes[i].getY() - 11.5f);
        index += 2;
    }
}

void Level::updatePipes() {
    double rand1 = rand() / double(RAND_MAX);
    pipes[index % 10] = Pipe(OFFSET + index * 3.0f, rand1 * 4.0f);
    pipes[(index + 1) % 10] = Pipe(pipes[index % 10].getX(), pipes[index % 10].getY() - 11.5f);
    index += 2;
}

bool Level::collision() {
    for (int i = 0; i < 5 * 2; i++) {
        float bx = -xScroll * 0.05f;
        float by = bird.getY();
        float px = pipes[i].getX();
        float py = pipes[i].getY();

        float bx0 = bx - bird.getSize() / 2.0f;
        float bx1 = bx + bird.getSize() / 2.0f;
        float by0 = by - bird.getSize() / 2.0f;
        float by1 = by + bird.getSize() / 2.0f;

        float px0 = px;
        float px1 = px + Pipe::getWidth();
        float py0 = py;
        float py1 = py + Pipe::getHeight();

        if (bx1 > px0 && bx0 < px1) {
            if (by1 > py0 && by0 < py1) {
                return true;
            }
        }
    }
    return false;
}

void Level::renderPipes() {
    Shader::PIPE.enable();
    Shader::PIPE.setUniform2f("bird", 0, bird.getY());

    glm::mat4 tran = glm::mat4(1.0f);
    tran = glm::translate(tran, glm::vec3(xScroll * 0.05f, 0.0f, 0.0f));

    Shader::PIPE.setUniformMat4f("vw_matrix", tran);
    Pipe::texture.bind();
    Pipe::mesh.bind();

    for (int i = 0; i < 5 * 2; i++) {
        Shader::PIPE.setUniformMat4f("ml_matrix", pipes[i].getModelMatrix());
        Shader::PIPE.setUniform1i("top", i % 2 == 0 ? 1 : 0);
        Pipe::mesh.draw();
    }
    Pipe::mesh.unbind();
    Pipe::texture.unbind();

}

bool Level::isGameOver() {
    return reset;
}

