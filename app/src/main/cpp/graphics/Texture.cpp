//
// Created by Nemo li on 2020/6/6.
//

#include <GLES3/gl32.h>
#include "Texture.h"
#include "../CLogger.h"

Texture::Texture() {

}

Texture::Texture(string path) {
    CLOGD("加载图片%s", path.c_str());
    unsigned char *image = jniHelper->ExtractAssetImage(path);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 100, 100, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glBindTexture(GL_TEXTURE_2D, 0);
//    CLOGD("创建的texture %d", texture);
}

Texture::~Texture() {
    unbind();
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, texture);
    CLOGD("使用的texture %d", texture);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
