#include "GraphicsHelper.hpp"
#include "SDLBox.hpp"
#include <string>
#include <iostream>
#include <algorithm> // std::min

#define _USE_MATH_DEFINES
#include <cmath>

using std::string;
using std::runtime_error;
// math functions
using std::sin;
using std::cos;
using std::atan2;
using std::atan;
using std::round;
using std::sqrt;

std::map<std::string, sdlbox::Font*> sdlbox::GraphicsHelper::loadedFonts;

std::string sdlbox::GraphicsHelper::defaultFont = "";

SDL_Color sdlbox::GraphicsHelper::backup;

sdlbox::Texture* sdlbox::GraphicsHelper::createTexture(SDL_Surface* surf, bool freesrc) {
    SDL_Renderer* renderer = SDLBox::getInstance()->getRenderer();
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);

    int w = surf->w;
    int h = surf->h;
    
    if (freesrc) {
        SDL_FreeSurface(surf);
    }

    if (texture == NULL) {
        throw runtime_error("Error creating texture from surface: " + string(SDL_GetError()));
    }
    
    return new Texture(texture, w, h);
}

sdlbox::Font* sdlbox::GraphicsHelper::getDefaultFont(int size) {
    if (!defaultFont.empty()) {
        // Theoretically, the following may fail, but only if the font file in
        /// question was moved since it was first accessed, and the size also is
        // different
        return tryLoadFont(defaultFont, size); // shouldn't throw exception
    }

    // some okay-ish default values
    // default.ttf should be in project root folder or in res folder
    string options[] = {"default.ttf", "calibri.ttf", "arial.ttf", "times.ttf"};

    for (auto opt : options) {
        auto key = opt + std::to_string(size);
        try {
            loadedFonts[key] = new Font(opt, size); // may throw runtime_error
            defaultFont = opt;
            return loadedFonts[key];
        } catch (const runtime_error &err) {
            // move on to next option
            // also, I should create custom exceptions...
        }
    }

    throw runtime_error("Error loading default font: No font file found");
}

string sdlbox::GraphicsHelper::getDefaultFontName() {
    if (defaultFont.empty()) {
        getDefaultFont(); // figure out default font name
    }
    return defaultFont;
}

sdlbox::Font* sdlbox::GraphicsHelper::tryLoadFont(const string &filename, int size) {
    string key = filename + std::to_string(size);
    auto font = loadedFonts.find(key);
    
    if (font != loadedFonts.end()) {
        return font->second;
    }
    
    Font* f = new Font(filename, size); // may throw runtime_error
    loadedFonts[key] = f;
    return f;
}

void sdlbox::GraphicsHelper::freeLoadedFonts() {
    for (auto f : loadedFonts) {
        delete f.second;
    }
}

void sdlbox::GraphicsHelper::drawRect(SDL_Rect* where, const Color &color, bool fill) {
    // finally, a draw method which is blessedly simple
    SDL_Renderer* renderer = SDLBox::getInstance()->getRenderer();
    setColor(renderer, color);
    if (fill) {
        SDL_RenderFillRect(renderer, where);
    }
    else {
        // I won't bother with stroke thickness (yet, at least)
        SDL_RenderDrawRect(renderer, where);
    }
    
    restoreColor(renderer);
}

void sdlbox::GraphicsHelper::drawCircle(int x0, int y0, int radius, const Color &color, int linewidth, int fillDirection) {
    // NOTE: radius is given as an integer because it's easier
    // Also, the algorithm is basically ripped off of Wikipedia. Yay!
    // TODO: Implement in all the other draw methods too
    
    SDL_Renderer* renderer = SDLBox::getInstance()->getRenderer();
    setColor(renderer, color);

    int x1,x2;
    if (fillDirection < 0) {
        x1 = radius;
        x2 = radius - linewidth;
    }
    else if (fillDirection > 0) {
        x1 = radius + linewidth;
        x2 = radius;
    }
    else {
        x1 = radius + linewidth/2 + linewidth % 2;
        x2 = radius - linewidth/2;
    }
    int y = 0;
    int err1 = 0;
    int err2 = 0;

    std::function<void (int,int,int,bool)> plot;


    if (linewidth > 1) {
        plot = [&](int a, int b, int c, bool horizontal) {
            if (horizontal)
                SDL_RenderDrawLine(renderer, x0 + a, y0 + c, x0 + b, y0 + c);
            else
                SDL_RenderDrawLine(renderer, x0 + c, y0 + a, x0 + c, y0 + b);
        };
    }
    else if (linewidth == 1){
        // makes linewidth=1 follow the original midpoint circle algorithm
        plot = [&](int a, int b, int c, bool horizontal) {
            if (horizontal)
                SDL_RenderDrawPoint(renderer, x0 + a, y0 + c);
            else
                SDL_RenderDrawPoint(renderer, x0 + c, y0 + a);
        };
    }
    else {
        return; // don't draw anything
    }

    while (x1 >= y || x2 >= y) {
        plot(x1, x2, y, true);
        plot(x1, x2, -y, true);
        plot(-x1, -x2, y, true);
        plot(-x1, -x2, -y, true);
        plot(x1, x2, y, false);
        plot(-x1, -x2, y, false);
        plot(x1, x2, -y, false);
        plot(-x1, -x2, -y, false);
        
        y += 1;
        if (err1 <= 0) {
            err1 += 2*y + 1;
        }
        if (err1 > 0) {
            x1 -= 1;
            err1 -= 2*x1 + 1;
        }
        if (err2 <= 0) {
            err2 += 2*y + 1;
        }
        if (err2 > 0) {
            x2 -= 1;
            err2 -= 2*x2 + 1;
        }
    }

    restoreColor(renderer);
}

// uses midpoint ellipse algorithm: see https://stackoverflow.com/a/15482128/4498826
void sdlbox::GraphicsHelper::drawEllipse(SDL_Rect* where, const Color &color, int linewidth, int fillDirection) {
    SDL_Renderer* renderer = SDLBox::getInstance()->getRenderer();
    setColor(renderer, color);
    
    int a = where->w / 2;
    int b = where->h / 2;

    int x0 = where->x + a;
    int y0 = where->y + b;

    // NOTE: I gave up
    if (linewidth > 1) {
        equationEllipse(renderer, x0, y0, a, b, linewidth, fillDirection);
    }
    else if (linewidth == 1) {
        midpointEllipse(renderer, x0, y0, a, b);
    }
    
    restoreColor(renderer);
}

void sdlbox::GraphicsHelper::midpointEllipse(SDL_Renderer* renderer, int x0, int y0, int a, int b) {
    auto plot = [&](int x, int y) {
        SDL_RenderDrawPoint(renderer, x0+x, y0+y);
        SDL_RenderDrawPoint(renderer, x0+x, y0-y);
        SDL_RenderDrawPoint(renderer, x0-x, y0+y);
        SDL_RenderDrawPoint(renderer, x0-x, y0-y);
    };
    
    int aa = a*a;
    int bb = b*b;
    
    int x = 0;
    int y = b;

    int p;
    int px = 0;
    int py = 2 * aa * y;

    plot(x, y);

    p = round(bb - (b*aa) + (0.25*aa));
    while (px < py) {
        x++;
        px += 2*bb;
        if (p < 0) {
            p += bb + px;
        }
        else {
            y--;
            py -= 2*aa;
            p += bb + px - py;
        }
        plot(x, y);
    }

    
    int x05 = (x+0.5)*(x+0.5);
    int y1 = (y-1)*(y-1);
    
    p = round(bb * x05 + aa * y1 - aa * bb);
    while (y > 0) {
        y--;
        py -= 2 * aa;
        if (p > 0) {
            p += aa - py;
        }
        else {
            x++;
            px += 2 * bb;
            p += aa - py + px;
        }
        plot(x, y);
    }
}

void sdlbox::GraphicsHelper::equationEllipse(SDL_Renderer* renderer, int x0, int y0, int a, int b, int linewidth, int fillDirection) {
    int oa, ia;
    int ob, ib;
    if (fillDirection < 0) {
        // fill inwards
        oa = a;
        ia = a - linewidth;
        ob = b;
        ib = b - linewidth;
    }
    else if (fillDirection > 0) {
        // fill outwards
        oa = a + linewidth;
        ia = a;
        ob = b + linewidth;
        ib = b;
    }
    else {
        // fill half both ways
        oa = a + linewidth/2; // TODO: put remainder here, below, or drop?
        ia = a - linewidth/2;
        ob = b + linewidth/2;
        ib = b - linewidth/2;
    }
    int oaa = oa*oa;
    int obb = ob*ob;
    int oaabb = oaa*obb;
    int iaa = ia*ia;
    int ibb = ib*ib;
    int iaabb = iaa*ibb;
    for (int x = -oa; x <= oa; x++) {
        for (int y = -ob; y <= ob; y++) {
            if (x*x*obb + y*y*oaa <= oaabb && x*x*ibb + y*y*iaa >= iaabb) {
                SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
            }
        }
    }
}

void sdlbox::GraphicsHelper::drawArc(int x0, int y0, int radius, double fromAngle, double toAngle, const Color &color) {
    SDL_Renderer* renderer = SDLBox::getInstance()->getRenderer();
    setColor(renderer, color);

    // NOTE: Angles are assumed to be in degrees, are converted to radians
    // internally.
    // NOTE: Angles in the 3rd and 4th quadrants are negative (-0 to -M_PI/2).
    // This means that if we want to draw a full circle arc we'd have to
    // (somewhat counter-intuitively) have to draw from -M_PI/2 to M_PI/2. There
    // is no way to draw a single arc spanning (for instance) only the 2nd and
    // 3rd quadrant. TODO: Fix this.
    // NOTE: A possible solution is to convert any degree d returned by atan2 to
    // -(d-M_PI/2) and operate with degrees from 0-360 as passed per parameter
    // TODO: Implement arbitrary stroke thickness (this is far from a priority
    // right now)

    // make it so that fromAngle is the smallest and toAngle is the biggest
    if (fromAngle > toAngle) {
        auto tmp = fromAngle;
        fromAngle = toAngle;
        toAngle = tmp;
    }

    double fromAngleRad = M_PI * fromAngle / 180;
    double toAngleRad = M_PI * toAngle / 180;

    int x = radius;
    int y = 0;
    int err = 0;

    // NOTE: In the below functions, I was squeamish about reusing "x" and "y"
    // since it captures from the outside, so I changed it to "X" and "Y". It
    // would probably have worked, but whatever, I'm not changing it now.
    
    // A small note on the (at least for me) non-intuitive atan2-call:
    // Apparently, to get the correct atan2 return value, you need to call it
    // with (y, x) instead of (x, y) - don't ask me why. Furthermore, since
    // computers flip the Y axis but maths don't, we need to flip the sign of
    // the Y argument. This produces the correct result, in any case!
    auto isOkay = [&](int X, int Y) {
        return atan2(-Y, X) >= fromAngleRad && atan2(-Y, X) <= toAngleRad;
    };
    
    auto plot = [&](int X, int Y) {
        if (isOkay(X,Y))
            SDL_RenderDrawPoint(renderer, x0+X, y0+Y);
        if (isOkay(X,-Y))
            SDL_RenderDrawPoint(renderer, x0+X, y0-Y);
        if (isOkay(-X,Y))
            SDL_RenderDrawPoint(renderer, x0-X, y0+Y);
        if (isOkay(-X,-Y))
            SDL_RenderDrawPoint(renderer, x0-X, y0-Y);
            // draw (y, x)
        if (isOkay(Y,X))
            SDL_RenderDrawPoint(renderer, x0+Y, y0+X);
        if (isOkay(Y,-X))
            SDL_RenderDrawPoint(renderer, x0+Y, y0-X);
        if (isOkay(-Y,X))
            SDL_RenderDrawPoint(renderer, x0-Y, y0+X);
        if (isOkay(-Y,-X))
            SDL_RenderDrawPoint(renderer, x0-Y, y0-X);
    };
    

    while (x >= y) {
        // draw (x, y)
        plot(x, y);

        y += 1;
        if (err <= 0) {
            err += 2*y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2*x + 1;
        }
    }

    restoreColor(renderer);
}

void sdlbox::GraphicsHelper::drawRoundedRect(SDL_Rect* where, int r, const Color &color) {
    // What follows is the ugliest code I have written thus far for this
    // project, and I hope I will never have to look at it again.
    
    SDL_Renderer* renderer = SDLBox::getInstance()->getRenderer();
    setColor(renderer, color);
    
    int left = where->x;
    int right = where->x + where->w;
    int top = where->y;
    int bottom = where->y + where->h;
    
    int x0 = where->x + r;
    int x1 = where->x + where->w - r;
    int x2 = x1;
    int x3 = x0;

    int y0 = where->y + r;
    int y1 = y0;
    int y2 = where->y + where->h - r;
    int y3 = y2;
    
    // top line
    SDL_RenderDrawLine(renderer, x0, top, x1, top);

    // right line
    SDL_RenderDrawLine(renderer, right, y1, right, y2);

    // bottom line
    SDL_RenderDrawLine(renderer, x2, bottom, x3, bottom);

    // left line
    SDL_RenderDrawLine(renderer, left, y3, left, y0);

    // have to restore here, since drawArc uses its own set/restore arcs
    restoreColor(renderer);
    
    drawArc(x0, y0, r, 180, 90, color);
    drawArc(x1, y1, r, 90, 0, color);
    drawArc(x2, y2, r, 0, -90, color);
    drawArc(x3, y3, r, -90, -180, color);
//    drawArc(x1, y1, x2, y2, r, color);
//    drawArc(x2, y2, x3, y3, r, color);
//    drawArc(x3, y3, x0, y0, r, color);
}

void sdlbox::GraphicsHelper::setColor(SDL_Renderer* renderer, const Color &color) {
    SDL_GetRenderDrawColor(renderer, &backup.r, &backup.g, &backup.b, &backup.a);
    auto c = color.toSDLColor();
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

void sdlbox::GraphicsHelper::restoreColor(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, backup.r, backup.g, backup.b, backup.a);
}
