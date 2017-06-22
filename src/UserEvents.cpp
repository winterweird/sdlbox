#include "UserEvents.hpp"
#include <SDL2/SDL.h>

std::map<std::string, int> sdlbox::UserEvents::eventCodes;

bool sdlbox::UserEvents::eventRegistered(std::string name) {
    return eventCodes.find(name) != eventCodes.end();
}

unsigned int sdlbox::UserEvents::eventCode(std::string name) {
    auto e = eventCodes.find(name);
    if (e != eventCodes.end()) {
        return e->second;
    }

    unsigned int code = SDL_RegisterEvents(1);
    if (code == ((Uint32)-1)) {
        throw std::runtime_error("Register event error: no more unique event codes");
    }

    eventCodes[name] = code;
    return code;
}

unsigned int sdlbox::UserEvents::existingEventCode(std::string name) {
    // check that the event code actually exists
    auto e = eventCodes.find(name);
    if (e != eventCodes.end()) {
        return e->second;
    }

    throw std::runtime_error("Fetch event error: User event " + std::string(name) + " does not exist");
}
