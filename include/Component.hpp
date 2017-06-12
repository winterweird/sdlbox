#ifndef INCLUDE_COMPONENT_HPP_HEADER_GUARD_258033191213708
#define INCLUDE_COMPONENT_HPP_HEADER_GUARD_258033191213708

#include <SDL2/SDL.h>

namespace sdlbox {
    class Component {
        public:
            virtual ~Component();
            
            virtual int getWidth() const = 0;
            virtual int getHeight() const = 0;

            virtual int getX() const;
            virtual int getY() const;

            virtual Component* withPosition(int x, int y);
            virtual Component* withPosition(Component* relative, int x, int y);

            virtual int getVerticalPadding() const;
            virtual int getHorizontalPadding() const;

            virtual Component* withVPad(int amount);
            virtual Component* withHPad(int amount);
            virtual Component* withPadding(int vPad, int hPad);

            // whether or not the specified component should receive its
            // position from its parent or not
            virtual bool receivePosition() const;
            
            virtual void draw() const = 0;

            virtual void handle(const SDL_Event &e);
            
            void addEventListener(int eventType, EventListener* l);
        private:
            int x, y;
            int vPad = 0, hPad = 0;

            std::map<int, EventListener*> eventListeners;
    };
}

#endif /* INCLUDE_COMPONENT_HPP_HEADER_GUARD_258033191213708 */
