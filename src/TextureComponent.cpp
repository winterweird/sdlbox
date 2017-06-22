#include "TextureComponent.hpp"

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

sdlbox::Component* sdlbox::TextureComponent::withPosition(int x, int y) {
    Component::withPosition(x, y);
    repositionTexture(0, 0);
    return this;
}

sdlbox::Component* sdlbox::TextureComponent::withPosition(Component* relative, int x, int y) {
    Component::withPosition(relative, x, y);
    repositionTexture(0, 0);
    return this;
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

void sdlbox::TextureComponent::repositionTexture(int xOffset, int yOffset) {
    if (texture != NULL)
        texture->withPosition(this, xOffset, yOffset);
}
