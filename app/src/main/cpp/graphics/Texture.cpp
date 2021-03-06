//
// Created by Nemo li on 2020/6/6.
//

#include <GLES3/gl32.h>
#include "Texture.h"
#include "../CLogger.h"
#include "../stb_image.h"

Texture::Texture() {

}

Texture::Texture(string path, bool png) {

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    unsigned char *image = jniHelper->ExtractAssetImage(path);
    if (png) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, jniHelper->imageW,
                     jniHelper->imageH, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     image);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, jniHelper->imageW,
                     jniHelper->imageH, 0, GL_RGB, GL_UNSIGNED_BYTE,
                     image);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(image);
}

Texture::~Texture() {
    unbind();
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
