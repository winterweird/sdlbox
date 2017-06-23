#include "SDLBox.hpp"
#include "GraphicsHelper.hpp"
#include "UserEvents.hpp"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <algorithm> // std::max
#include <mutex>
#include <cstdlib>
#include <ctime>

using std::string;
using std::runtime_error;
using std::max;

sdlbox::SDLBox* sdlbox::SDLBox::instance = NULL;

sdlbox::SDLBox::SDLBox(string title, int width, int height) : width(width), height(height) {
    init(title);
}

sdlbox::SDLBox::~SDLBox() {
    // destroy all children
    for (auto r : components) {
        for (auto c : r.second) {
            delete c;
        }
    }

    // destroy all components scheduled for destruction which we haven't
    // destroyed yet
    for (auto c : destroyList) {
        delete c;
    }

    // destroy all event listeners
    for (auto l : eventListeners) {
        delete l.second;
    }

    // delete loaded fonts
    GraphicsHelper::freeLoadedFonts();
    
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

void sdlbox::SDLBox::continuallyFitToContent() {
    this->addEventListener(UserEvents::existingEventCode("WINDOW_FIT_TO_CONTENT"),
        new EventListener([this](const SDL_Event &e) {
            this->repositionChildren();
        }));
}

void sdlbox::SDLBox::ctrlWToQuit() {
    this->addEventListener(SDL_KEYDOWN, new EventListener([](const SDL_Event &e) {
            if (e.key.keysym.sym == SDLK_w && e.key.keysym.mod & KMOD_CTRL) {
                SDL_Event e;
                e.type = SDL_QUIT;
                SDL_PushEvent(&e);
            }
        }));
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

void sdlbox::SDLBox::unfreezeSize() {
    unfreezeWidth();
    unfreezeHeight();
}

void sdlbox::SDLBox::unfreezeWidth() {
    autoResizeWidth = true;
}

void sdlbox::SDLBox::unfreezeHeight() {
    autoResizeHeight = true;
}

bool sdlbox::SDLBox::frozen() const {
    return frozenWidth() && frozenHeight();
}

bool sdlbox::SDLBox::frozenWidth() const {
    return !autoResizeWidth;
}

bool sdlbox::SDLBox::frozenHeight() const {
    return !autoResizeHeight;
}

int sdlbox::SDLBox::getFPS() const {
    return FPS;
}

int sdlbox::SDLBox::getWidth() const {
    return width;
}

int sdlbox::SDLBox::getHeight() const {
    return height;
}

int sdlbox::SDLBox::randint(int max) const {
    // adapted from: https://stackoverflow.com/a/822361/4498826
    
    if (max < 0) {
        throw runtime_error("randint: Max cannot be negative");
    }
    if (max == RAND_MAX)
        return rand();

    int oneMore = max+1;
    long end = RAND_MAX / oneMore;
    end *= oneMore;

    int r;
    while ((r = rand()) >= end);

    return r%oneMore;
}

int sdlbox::SDLBox::randint(int min, int max) const {
    if (min > max) {
        throw runtime_error("randint: Min cannot be greater than max");
    }
    return randint(max-min) + min;
}

void sdlbox::SDLBox::goToRoom(const Room &room) {
    if (roomSupport) {
        activeRoom = room;
        components[room]; // ensure room exists
    }
    else
        throw runtime_error("Changing room not supported in auto content fit mode");
}

sdlbox::Room sdlbox::SDLBox::getActiveRoom() const {
    return activeRoom;
}

void sdlbox::SDLBox::wipe() {
    wipe(activeRoom);
}

void sdlbox::SDLBox::wipe(const Room &room) {
    auto roomComponents = getRoomComponents(room);
    for (auto c : roomComponents) {
        delete c;
    }
    
    roomComponents.clear();
    components[room] = roomComponents; // update map content
}

void sdlbox::SDLBox::add(Component* c) {
    // short names:
    auto roomComponents = getRoomComponents(activeRoom);
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
    
    roomComponents.push_back(c);
    components[activeRoom] = roomComponents; // update map content
}

void sdlbox::SDLBox::scheduleDestruct(Component* c) {
    auto roomComponents = getRoomComponents(activeRoom);
    auto i = find(roomComponents.begin(), roomComponents.end(), c);
    if (i != roomComponents.end()) {
        roomComponents.erase(i);
        components[activeRoom] = roomComponents; // update map content
        
        destroyList.push_back(c);
    }
}

void sdlbox::SDLBox::draw() const {
    SDL_RenderClear(renderer);

    auto roomComponents = getRoomComponents(activeRoom);
    for (auto c : roomComponents) {
        c->draw();
    }

    SDL_RenderPresent(renderer);
}

void sdlbox::SDLBox::handle(const SDL_Event &e) {
    auto l = eventListeners.find(e.type);
    if (l != eventListeners.end())
        (l->second)->handle(e);
    
    auto roomComponents = getRoomComponents(activeRoom);
    for (auto c : roomComponents) {
        c->handle(e);
    }
}

void sdlbox::SDLBox::step() {
    for (auto c : destroyList) {
        delete c;
    }
    destroyList.clear();
    
    auto roomComponents = getRoomComponents(activeRoom);
    for (auto c : roomComponents) {
        c->step();
    }
}

void sdlbox::SDLBox::addEventListener(int eventType, EventListener* l) {
    eventListeners[eventType] = l;
}

void sdlbox::SDLBox::repositionChildren() {
    int nx = 0;
    int ny = 0;
    int w = 1;
    int h = 1;

    auto roomComponents = getRoomComponents(activeRoom);
    for (size_t i = 0; i < roomComponents.size(); i++) {
        auto c = roomComponents[i];
        if (!c->receivePosition()) continue;
        
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

    if (width <= 0) {
        autoResizeWidth = true;
        width = 1;
        roomSupport = false;
    }
    if (height <= 0) {
        autoResizeHeight = true;
        height = 1;
        roomSupport = false;
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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // fuck VSYNC

    if (renderer == NULL) {
        throw runtime_error("SDL renderer create error: " + string(SDL_GetError()));
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // TODO: also initialize image and sound modules
    if (TTF_Init() == -1) {
        throw runtime_error("TTF init error: " + string(TTF_GetError()));
    }

    // set up event codes
    UserEvents::eventCode("WINDOW_FIT_TO_CONTENT");

    components[activeRoom]; // create initial room

    // init RNG
    srand(time(NULL));

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

std::vector<sdlbox::Component*> sdlbox::SDLBox::getRoomComponents(const Room &room) const {
    auto r = components.find(room);
    if (r == components.end()) {
        throw runtime_error("Room not found: " + room.str());
    }

    return r->second;
}
