//
// Created by Nemo li on 2020/6/10.
//

#ifndef FLAPPY_FADE_H
#define FLAPPY_FADE_H


#include "../graphics/VertexArray.h"

class Fade {
public:
    Fade();

    void render(int time);

    virtual ~Fade();

private:
    VertexArray *mesh;
};


#endif //FLAPPY_FADE_H
