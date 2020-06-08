//
// Created by Nemo li on 2020/6/6.
//

#ifndef FLAPPY_TEXTURE_H
#define FLAPPY_TEXTURE_H

#include <string>
#include "../JNIHelper.h"
#include "GLES3/gl32.h"

using namespace std;

class Texture {
public:
    Texture();

    Texture(string path, bool png);

    virtual ~Texture();

    void bind();

    void unbind();

private:
    int *width, *height;
    GLuint texture;
};

extern JNIHelper *jniHelper;

#endif //FLAPPY_TEXTURE_H
