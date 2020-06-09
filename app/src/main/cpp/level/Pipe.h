//
// Created by Nemo li on 2020/6/6.
//

#ifndef FLAPPY_PIPE_H
#define FLAPPY_PIPE_H


#include "../graphics/Texture.h"
#include "../graphics/VertexArray.h"
#include "glm.hpp"

class Pipe {
private:
    static float width, height;
    glm::vec3 position;
    glm::mat4 ml_matrix;

public:
    Pipe();

    Pipe(float x, float y);

    static void create();

    float getX();

    float getY();

    glm::mat4 getModelMatrix();

    static VertexArray getMesh();

    static Texture getTexture();

    static float getWidth();

    static float getHeight();

    virtual ~Pipe();

    static Texture texture;

    static VertexArray mesh;
};


#endif //FLAPPY_PIPE_H
