#include "Color.hpp"

sdlbox::Color::Color(int r, int g, int b, int a) {
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
}

SDL_Color sdlbox::Color::toSDLColor() const {
    return color;
}

