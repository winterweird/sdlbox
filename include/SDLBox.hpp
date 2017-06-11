#ifndef INCLUDE_SDLBOX_HPP_HEADER_GUARD_27166598727960
#define INCLUDE_SDLBOX_HPP_HEADER_GUARD_27166598727960

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "Component.hpp"
#include "Layout.hpp"

namespace sdlbox {
    class SDLBox {
        public:
            SDLBox(std::string title, int width=0, int height=0);
            ~SDLBox();

            void setOrientation(int orientation);
            void add(Component* c);

            void draw() const;

            static SDLBox* getInstance();
            SDL_Renderer* getRenderer() const;
        private:
            int width, height;
            int nextX = 0;
            int nextY = 0;
            bool autoResizeWidth, autoResizeHeight;
            int orientation = Layout::VERTICAL;
            
            SDL_Window* window;
            SDL_Renderer* renderer;

            static SDLBox* instance;

            std::vector<Component*> components;

            // helper methods
            void init(std::string title);
            void resize(int w, int h);
    };
}

#endif /* INCLUDE_SDLBOX_HPP_HEADER_GUARD_27166598727960 */
