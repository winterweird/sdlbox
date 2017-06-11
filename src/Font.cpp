#include "Font.hpp"
#include "SDLBox.hpp"
#include "GraphicsHelper.hpp"
#include <iostream>

using std::string;
using std::runtime_error;

sdlbox::Font::Font(string filename, int size) {
    font = TTF_OpenFont(filename.c_str(), size);
    if (font == NULL) {
        font = TTF_OpenFont(("res/"+filename).c_str(), size);
    }
    if (font == NULL) {
        // window system font?
        font = TTF_OpenFont(("C:/Windows/Font/"+filename).c_str(), size);
    }
    if (font == NULL) {
        // give up
        throw runtime_error("Error loading font " + filename + ": " + string(TTF_GetError()));
    }
}

sdlbox::Font::~Font() {
    // NOTE: This might create problems down the road if I copy font objects by
    // passing them as parameters or whatever... If that happens, either switch
    // to using pointers and keep track of all your font objects, or create a
    // copy constructor or something.
    TTF_CloseFont(font);
}

sdlbox::Texture* sdlbox::Font::render(string text, const Color & color) {
    SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color.toSDLColor());
    if (surf == NULL) {
        throw runtime_error("Error creating text surface: " + string(TTF_GetError()));
    }

    return GraphicsHelper::createTexture(surf);
}

sdlbox::Texture* sdlbox::Font::renderBlended(string text, const Color &color) {
    SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), color.toSDLColor());
    if (surf == NULL) {
        throw runtime_error("Error creating text surface: " + string(TTF_GetError()));
    }

    return GraphicsHelper::createTexture(surf);
}

sdlbox::Texture* sdlbox::Font::renderShaded(string text, const Color &fgColor, const Color &bgColor) {
    SDL_Surface* surf = TTF_RenderText_Shaded(font, text.c_str(),
            fgColor.toSDLColor(), bgColor.toSDLColor());

    if (surf == NULL) {
        throw runtime_error("Error creating text surface: " + string(TTF_GetError()));
    }

    return GraphicsHelper::createTexture(surf);
}

int sdlbox::Font::getTextWidth(std::string text) const {
    int w, h;
    getTextDimensions(text, w, h);
    return w;
}

int sdlbox::Font::getTextHeight(std::string text) const {
    int w, h;
    getTextDimensions(text, w, h);
    return h;
}

void sdlbox::Font::getTextDimensions(std::string text, int& w, int& h) const {
    TTF_SizeText(font, text.c_str(), &w, &h);
}
