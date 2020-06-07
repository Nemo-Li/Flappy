//
// Created by Nemo li on 2020/6/6.
//

#ifndef FLAPPY_BIRD_H
#define FLAPPY_BIRD_H


#include "../graphics/VertexArray.h"
#include "../graphics/Texture.h"
#include "glm.hpp"
#include "../graphics/Shader.h"


class Bird {
private:
    float size = 1.0f;
    VertexArray *mesh;
    Texture *texture;
    glm::vec3 position;
    float rot = 60.0f;
    float delta = 0.0f;

public:
    Bird();
    virtual ~Bird();
    void update();
    void fall();
    void render();
    float getY();
    float getSize();
};


#endif //FLAPPY_BIRD_H
