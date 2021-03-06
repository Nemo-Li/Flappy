//
// Created by Nemo li on 2020/6/6.
//

#ifndef FLAPPY_LEVEL_H
#define FLAPPY_LEVEL_H


#include "../graphics/VertexArray.h"
#include "../graphics/Texture.h"
#include "Bird.h"
#include "../graphics/Shader.h"
#include "Pipe.h"
#include "Fade.h"

class Level {
public:
    Level();

    void render();

    void update();

    virtual ~Level();

    bool isGameOver();

private:
    VertexArray background;
    Texture bgTexture;
    Bird bird;
    Fade fade;
    int map = 0;
    int xScroll = 0;

    Pipe pipes[5 * 2];
    int index = 0;
    float OFFSET = 5.0f;
    bool control = true, reset = false;
    float time = 0.0f;

    void createPipes();

    void updatePipes();

    bool collision();

    void renderPipes();
};


#endif //FLAPPY_LEVEL_H
