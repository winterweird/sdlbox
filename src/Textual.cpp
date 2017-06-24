#include "Textual.hpp"
#include "GraphicsHelper.hpp"
#include "SDLBox.hpp"
#include <iostream> // testing

sdlbox::Textual::~Textual() {
    if (this->fgColor != NULL)
        delete this->fgColor;

    if (this->bgColor != NULL)
        delete this->bgColor;
}

void sdlbox::Textual::setText(const std::string &text, bool blended) {
    setText(GraphicsHelper::getDefaultFontName(), 20, text, new Color(0, 0, 0), NULL, blended);
}

void sdlbox::Textual::setText(const std::string &font, const std::string &text, bool blended) {
    setText(font, 20, text, new Color(0, 0, 0), NULL, blended);
}

void sdlbox::Textual::setText(const std::string &text, const Color &color, bool blended) {
    setText(GraphicsHelper::getDefaultFontName(), 20, text, new Color(color), NULL, blended);
}

void sdlbox::Textual::setText(const std::string &font, const std::string &text, const Color &c, bool blended) {
    setText(font, 20, text, new Color(c), NULL, blended);
}

void sdlbox::Textual::setText(const std::string &text, const Color & fg, const Color &bg) {
    setText(GraphicsHelper::getDefaultFontName(), 20, text, new Color(fg), new Color(bg), false);
}

void sdlbox::Textual::setText(const std::string &font, const std::string &text, const Color &fg, const Color &bg) {
    setText(font, 20, text, new Color(fg), new Color(bg), false);
}

void sdlbox::Textual::setMessage(const std::string &message) {
    this->msg = message;
}

void sdlbox::Textual::setFont(const std::string &font, int size, bool blended) {
    this->fontName = font;
    this->fontSize = size;
    this->blended = blended;
}

void sdlbox::Textual::setForeground(Color* color) {
    if (this->fgColor != NULL) {
        delete this->fgColor;
    }
    this->fgColor = color;
}

void sdlbox::Textual::setBackground(Color* color) {
    if (this->bgColor != NULL) {
        delete this->bgColor;
    }
    this->bgColor = color;
}

std::string sdlbox::Textual::getMessage() const {
    return this->msg;
}

std::string sdlbox::Textual::getFontName() const {
    return this->fontName;
}

sdlbox::Font* sdlbox::Textual::getFont() const {
    return GraphicsHelper::tryLoadFont(fontName, fontSize);
}

sdlbox::Color* sdlbox::Textual::getForeground() const {
    return fgColor;
}

sdlbox::Color* sdlbox::Textual::getBackground() const {
    return bgColor;
}

bool sdlbox::Textual::textIsBlended() const {
    return bgColor == NULL && blended;
}

// protected
void sdlbox::Textual::setText(const std::string &font, int size, const std::string &text, Color* fg, Color* bg, bool blended) {
    setMessage(text);
    setFont(font, size, blended);
    setForeground(fg);
    setBackground(bg);
}

void sdlbox::Textual::commit() {
    // assumes text is set and such and such
    TextureComponent::setTexture(createTexture());
    TextureComponent::commit();
    
    SDLBox::getInstance()->repositionChildren(); // update change in UI
}

sdlbox::Texture* sdlbox::Textual::createTexture() const {
    Texture* t;
    auto font = GraphicsHelper::tryLoadFont(this->fontName);
    
    if (this->bgColor != NULL) {
        // create shaded text
        t = font->renderShaded(msg, *this->fgColor, *this->bgColor);
    }
    else if (blended) {
        t = font->renderBlended(msg, *this->fgColor);
    }
    else {
        t = font->render(msg, *this->fgColor);
    }
    
    return t;
}
