#include "SDLBox.hpp"
#include "GraphicsHelper.hpp"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <algorithm> // std::max
#include <mutex>

using std::string;
using std::runtime_error;
using std::max;

sdlbox::SDLBox* sdlbox::SDLBox::instance = NULL;

sdlbox::SDLBox::SDLBox(string title, int width, int height) : width(width), height(height) {
    init(title);
}

sdlbox::SDLBox::~SDLBox() {
    // destroy all children
    for (auto c : components) {
        delete c;
    }

    // delete default font
    Font* f = GraphicsHelper::getDefaultFont();
    delete f;
    
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void sdlbox::SDLBox::setOrientation(int orientation) {
    if (orientation != Layout::HORIZONTAL && orientation != Layout::VERTICAL) {
        throw runtime_error("Illegal orientation: " + std::to_string(orientation));
    }
    
    this->orientation = orientation;
}

void sdlbox::SDLBox::setFPS(int fps) {
    if (fps < 1) {
        throw runtime_error("FPS must be a positive number");
    }

    this->FPS = fps;
}

void sdlbox::SDLBox::freezeSize() {
    freezeWidth();
    freezeHeight();
}

void sdlbox::SDLBox::freezeWidth() {
    autoResizeWidth = false;
}

void sdlbox::SDLBox::freezeHeight() {
    autoResizeHeight = false;
}

int sdlbox::SDLBox::getFPS() const {
    return FPS;
}


void sdlbox::SDLBox::add(Component* c) {
    // short names:
    int lPad, rPad, tPad, bPad;
    c->getPadding(lPad, rPad, tPad, bPad);
    
    if (c->receivePosition()) {
        c->withPosition(nextX + lPad, nextY + tPad);
        if (orientation == Layout::VERTICAL) {
            nextY += c->getHeight() + tPad + bPad;
        }
        else if (orientation == Layout::HORIZONTAL) {
            nextX += c->getWidth() + lPad + rPad;
        }
        // else: idk
    }

    if (autoResizeWidth || autoResizeHeight) {
        int w = width;
        int h = height;
        
        if (autoResizeWidth) {
            w = max(c->getX() + c->getWidth() + rPad, w);
        }
        if (autoResizeHeight) {
            h = max(c->getY() + c->getHeight() + bPad, h);
        }

        resize(w, h);
    }
    
    components.push_back(c);
}

void sdlbox::SDLBox::draw() const {
    SDL_RenderClear(renderer);

    for (auto c : components) {
        c->draw();
    }

    SDL_RenderPresent(renderer);
}

void sdlbox::SDLBox::handle(const SDL_Event &e) {
    for (auto c : components) {
        c->handle(e);
    }
}

void sdlbox::SDLBox::repositionChildren() {
    int nx = 0;
    int ny = 0;
    int w = 1;
    int h = 1;

    for (size_t i = 0; i < components.size(); i++) {
        auto c = components[i];
        
        int lPad, rPad, tPad, bPad;
        c->getPadding(lPad, rPad, tPad, bPad);
        
        c->withPosition(nx + lPad, ny + tPad);
        
        if (orientation == Layout::VERTICAL) {
            ny += c->getHeight() + tPad + bPad;
        }
        else if (orientation == Layout::HORIZONTAL) {
            nx += c->getWidth() + lPad + rPad;
        }

        // calculate new required width/height
        if (autoResizeWidth) {
            w = max(c->getX() + c->getWidth() + rPad, w);
        }
        if (autoResizeHeight) {
            h = max(c->getY() + c->getHeight() + bPad, h);
        }
    }
    
    if (autoResizeWidth || autoResizeHeight) {
        resize(w, h);
    }

    nextX = nx;
    nextY = ny;
}

sdlbox::SDLBox* sdlbox::SDLBox::getInstance() {
    if (instance == NULL) {
        throw runtime_error("Cannot get instance: no window has been created");
    }
    return instance;
}

SDL_Renderer* sdlbox::SDLBox::getRenderer() const {
    return renderer;
}

void sdlbox::SDLBox::init(string title) {
    if (instance) {
        throw runtime_error("Cannot start a new SDLBox - another is running");
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw runtime_error("SDL init error: " + string(SDL_GetError()));
    }

    // TODO: Simply passing width/height to the window like this is broken if we
    // operate with variable sized windows. I need to fix that.
    
    if (width <= 0) {
        autoResizeWidth = true;
        width = 1;
    }
    if (height <= 0) {
        autoResizeHeight = true;
        height = 1;
    }
    
    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width,
                              height,
                              SDL_WINDOW_SHOWN);

    if (window == NULL) {
        throw runtime_error("SDL window create error: " + string(SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL) {
        throw runtime_error("SDL renderer create error: " + string(SDL_GetError()));
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // TODO: also initialize image and sound modules
    if (TTF_Init() == -1) {
        throw runtime_error("TTF init error: " + string(TTF_GetError()));
    }

    instance = this;
}

void sdlbox::SDLBox::resize(int w, int h) {
    if (w <= 0 || h <= 0) {
        throw runtime_error("Width/height must be greater than 0");
    }
    
    SDL_SetWindowSize(window, w, h);
    
    width = w;
    height = h;
}
