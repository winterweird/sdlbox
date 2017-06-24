#include "Label.hpp"
#include "GraphicsHelper.hpp"
#include "SDLBox.hpp"
#include "ComponentFactory.hpp"
#include <iostream> // testing

using std::string;

sdlbox::Label::Label(string text, bool blended) {
    Textual::setText(text, blended);
    ComponentFactory(this).padding(2, 2);
}

sdlbox::Label::Label(string text, const Color &color, bool blended) {
    Textual::setText(text, color, blended);
    ComponentFactory(this).padding(2, 2);
}

sdlbox::Label::Label(string text, const Color &fgColor, const Color &bgColor) {
    Textual::setText(text, fgColor, bgColor);
    ComponentFactory(this).padding(2, 2);
}

void sdlbox::Label::setText(const std::string &font, int size, const std::string &text, Color* fg, Color* bg, bool blended) {
    Textual::setText(font, size, text, fg, bg, blended);
    commit(); // actually make the texture
}
