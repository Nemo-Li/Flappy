//
// Created by Nemo li on 2020/6/6.
//

#ifndef FLAPPY_LEVEL_H
#define FLAPPY_LEVEL_H


#include "../graphics/VertexArray.h"
#include "../graphics/Texture.h"
#include "Bird.h"
#include "../graphics/Shader.h"

class Level {
public:
    Level();

    void render();

    void update();

    virtual ~Level();

private:
    VertexArray background, fade;
    Texture bgTexture;
    Bird bird;
    int map = 0;
    int xScroll = 0;
};


#endif //FLAPPY_LEVEL_H
