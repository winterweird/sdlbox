#ifndef INCLUDE_EVENTLISTENER_HPP_HEADER_GUARD_226111714414743
#define INCLUDE_EVENTLISTENER_HPP_HEADER_GUARD_226111714414743

#include <functional>
#include <SDL2/SDL.h>

namespace sdlbox {
    class EventListener {
        public:
            EventListener(std::function<void (const SDL_Event&)> callback);
            EventListener(std::function<bool (const SDL_Event&)> match,
                          std::function<void (const SDL_Event&)> callback);
            
            ~EventListener();

            void handle(const SDL_Event &e);
        private:
            std::function<void (const SDL_Event&)> callback;
            std::function<bool (const SDL_Event&)> match = [](const SDL_Event& e){return true;};
    };
}

#endif /* INCLUDE_EVENTLISTENER_HPP_HEADER_GUARD_226111714414743 */
