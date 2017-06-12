#include "Texture.hpp"
#include "SDLBox.hpp"

#include <iostream> // testing

sdlbox::Texture::Texture(SDL_Texture* texture, int w, int h) {
    this->texture = texture;
    this->width = w;
    this->height = h;
}

sdlbox::Texture::~Texture() {
    SDL_DestroyTexture(texture);
}

int sdlbox::Texture::getWidth() const {
    return width;
}

int sdlbox::Texture::getHeight() const {
    return height;
}

void sdlbox::Texture::draw() const {
    SDL_Rect r;
    r.w = this->getWidth();
    r.h = this->getHeight();
    r.x = this->getX();
    r.y = this->getY();

    SDL_Renderer* renderer = SDLBox::getInstance()->getRenderer();

    SDL_RenderCopy(renderer, texture, NULL, &r);
}
