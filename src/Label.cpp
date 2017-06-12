#include "Label.hpp"
#include "GraphicsHelper.hpp"
#include "SDLBox.hpp"
#include <iostream> // testing

using std::string;

sdlbox::Label::Label(string text, bool blended) {
    Font* font = GraphicsHelper::getDefaultFont();
    createTexture(font, text, Color(0,0,0), blended);
    withPadding(2, 2);
}

sdlbox::Label::Label(string text, Color color, bool blended) {
    Font* font = GraphicsHelper::getDefaultFont();
    createTexture(font, text, color, blended);
    withPadding(2, 2);
}

sdlbox::Label::Label(string text, Color fgColor, Color bgColor) {
    Font* font = GraphicsHelper::getDefaultFont();
    texture = font->renderShaded(text, fgColor, bgColor);
    
    withPadding(2, 2);
}

sdlbox::Label::~Label() {
    delete texture;
}

int sdlbox::Label::getWidth() const {
    return texture->getWidth();
}

int sdlbox::Label::getHeight() const {
    return texture->getHeight();
}

sdlbox::Component* sdlbox::Label::withPosition(int x, int y) {
    Component::withPosition(x, y);
    texture->withPosition(this, 0, 0);
    return this;
}

sdlbox::Component* sdlbox::Label::withPosition(Component* relative, int x, int y) {
    Component::withPosition(relative, x, y);
    texture->withPosition(this, 0, 0);
    return this;
}

void sdlbox::Label::setText(string text, bool blended) {
    auto font = GraphicsHelper::getDefaultFont();
    createTexture(font, text, Color(0,0,0), blended);
}

void sdlbox::Label::setText(Font* font, string text, bool blended) {
    createTexture(font, text, Color(0,0,0), blended);
}

void sdlbox::Label::setText(string text, Color color, bool blended) {
    auto font = GraphicsHelper::getDefaultFont();
    createTexture(font, text, color, blended);
}

void sdlbox::Label::setText(Font* font, string text, Color color, bool blended) {
    createTexture(font, text, color, blended);
}

void sdlbox::Label::draw() const {
    texture->draw();
}

// helper method
void sdlbox::Label::createTexture(Font* font, string text, Color color, bool blended) {
    if (blended) {
        texture = font->renderBlended(text, color);
    }
    else {
        texture = font->render(text, color);
    }

    //SDLBox::getInstance()->repositionChildren(); // update display // actually, don't
}
