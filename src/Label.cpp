#include "Label.hpp"
#include "GraphicsHelper.hpp"

using std::string;

sdlbox::Label::Label(string text, bool blended) {
    Font* font = GraphicsHelper::getDefaultFont();
    
    if (blended) {
        texture = font->renderBlended(text, Color(0,0,0));
    }
    else {
        texture = font->render(text, Color(0,0,0));
    }

    setPadding(2, 2);
}

sdlbox::Label::Label(string text, Color color, bool blended) {
    Font* font = GraphicsHelper::getDefaultFont();

    if (blended) {
        texture = font->renderBlended(text, color);
    }
    else {
        texture = font->render(text, color);
    }
    
    setPadding(2, 2);
}

sdlbox::Label::Label(string text, Color fgColor, Color bgColor) {
    Font* font = GraphicsHelper::getDefaultFont();
    texture = font->renderShaded(text, fgColor, bgColor);
    
    setPadding(2, 2);
}

int sdlbox::Label::getWidth() const {
    return texture->getWidth();
}

int sdlbox::Label::getHeight() const {
    return texture->getHeight();
}

void sdlbox::Label::setPosition(int x, int y) {
    Component::setPosition(x, y);
    texture->setPosition(this, 0, 0);
}

void sdlbox::Label::setPosition(Component* relative, int x, int y) {
    Component::setPosition(relative, x, y);
    texture->setPosition(this, 0, 0);
}



void sdlbox::Label::draw() const {
    texture->draw();
}
