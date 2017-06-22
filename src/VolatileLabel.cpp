#include "VolatileLabel.hpp"

sdlbox::VolatileLabel::VolatileLabel(std::string text) : Label(text) {}

sdlbox::VolatileLabel::VolatileLabel(std::string text, const Color &color) : Label(text, color) {}

sdlbox::VolatileLabel::VolatileLabel(std::string text, const Color &fg, const Color &bg) : Label(text, fg, bg) {}

void sdlbox::VolatileLabel::draw() const {
    // since the label is volatile, recreate texture every draw
    
    Texture* t = createTexture();
    t->withPosition(getX(), getY())->draw();
}

void sdlbox::VolatileLabel::setText(const std::string &font, int size, const std::string &text, Color* fg, Color* bg, bool blended) {
    Textual::setText(font, size, text, fg, bg, blended);
}

int sdlbox::VolatileLabel::getWidth() const {
    auto f = getFont();
    return f->getTextWidth(getMessage());
}

int sdlbox::VolatileLabel::getHeight() const {
    auto f = getFont();
    return f->getTextHeight(getMessage());
}
