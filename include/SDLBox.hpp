#ifndef INCLUDE_SDLBOX_HPP_HEADER_GUARD_27166598727960
#define INCLUDE_SDLBOX_HPP_HEADER_GUARD_27166598727960

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "Component.hpp"
#include "Layout.hpp"
#include "Room.hpp"

namespace sdlbox {
    class SDLBox {
        public:
            SDLBox(std::string title, int width=0, int height=0);
            ~SDLBox();

            void setOrientation(int orientation);
            void setFPS(int fps);

            // add event listeners which help handling things
            void continuallyFitToContent();
            void ctrlWToQuit();
            
            // freeze size
            void freezeSize();
            void freezeWidth();
            void freezeHeight();

            void unfreezeSize();
            void unfreezeWidth();
            void unfreezeHeight();

            bool frozen() const;
            bool frozenWidth() const;
            bool frozenHeight() const;
            
            int getFPS() const;
            int getWidth() const;
            int getHeight() const;
            
            // get random integers
            int randint(int max) const;
            int randint(int min, int max) const;

            void goToRoom(const Room &room);
            void wipe();
            void wipe(const Room &room);
            
            void add(Component* c);
            void scheduleDestruct(Component* c);

            void draw() const;

            void addEventListener(int eventType, EventListener* l);
            void handle(const SDL_Event & e);
            void step();

            void repositionChildren();

            static SDLBox* getInstance();
            SDL_Renderer* getRenderer() const;
        private:
            int width, height;
            int nextX = 0;
            int nextY = 0;
            bool autoResizeWidth, autoResizeHeight;
            int orientation = Layout::VERTICAL;
            int FPS = 60;

            Room activeRoom;
            
            SDL_Window* window = NULL;
            SDL_Renderer* renderer = NULL;

            static SDLBox* instance;

            std::vector<Component*> components;
            std::vector<Component*> destroyList; // for destruction each step
            std::map<int, EventListener*> eventListeners;

            // helper methods
            void init(std::string title);
            void resize(int w, int h);
    };
}

#endif /* INCLUDE_SDLBOX_HPP_HEADER_GUARD_27166598727960 */
