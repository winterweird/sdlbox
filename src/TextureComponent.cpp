#include "TextureComponent.hpp"
#include "ComponentFactory.hpp"
#include <iostream> // testing

sdlbox::TextureComponent::~TextureComponent() {
    if (texture != NULL)
        delete texture;
}

int sdlbox::TextureComponent::getWidth() const {
    return texture->getWidth();
}

int sdlbox::TextureComponent::getHeight() const {
    return texture->getHeight();
}

void sdlbox::TextureComponent::draw() const {
    texture->draw();
}

void sdlbox::TextureComponent::setTexture(Texture* t) {
    if (texture != NULL) {
        delete texture; // free old resources
    }
    texture = t;
}

void sdlbox::TextureComponent::commit() {
    repositionTexture(0, 0);
}

void sdlbox::TextureComponent::repositionTexture(int xOffset, int yOffset) {
    if (texture != NULL)
        ComponentFactory(texture).position(this, xOffset, yOffset);
}
