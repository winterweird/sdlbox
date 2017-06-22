#ifndef INCLUDE_COMPONENT_HPP_HEADER_GUARD_258033191213708
#define INCLUDE_COMPONENT_HPP_HEADER_GUARD_258033191213708

#include <SDL2/SDL.h>
#include <map>
#include <mutex>
#include <condition_variable>
#include "EventListener.hpp"

namespace sdlbox {
    extern std::mutex mtx;
    extern std::condition_variable cv;
    extern bool isDrawing;
    
    class Component {
        public:
            virtual ~Component();
            
            virtual int getWidth() const = 0;
            virtual int getHeight() const = 0;

            virtual int getX() const;
            virtual int getY() const;

            SDL_Rect getRect() const;

            virtual bool collides(Component* c) const; // check collision with other component

            virtual Component* withPosition(int x, int y);
            virtual Component* withPosition(Component* relative, int x, int y);

            virtual int getVerticalPadding() const;
            virtual int getHorizontalPadding() const;
            virtual int getLeftPadding() const;
            virtual int getRightPadding() const;
            virtual int getTopPadding() const;
            virtual int getBottomPadding() const;
            virtual void getPadding(int &lPad, int &rPad, int &tPad, int &bPad) const;

            // add padding
            virtual Component* withVPad(int amount); // vertical (top + bottom)
            virtual Component* withHPad(int amount); // horizontal (left + right)
            virtual Component* withLPad(int amount); // left
            virtual Component* withRPad(int amount); // right
            virtual Component* withTPad(int amount); // top
            virtual Component* withBPad(int amount); // bottom
            virtual Component* withPadding(int vPad, int hPad);
            virtual Component* withPadding(int lPad, int rPad, int tPad, int bPad);

            // whether or not the specified component should receive its
            // position from its parent or not
            virtual bool receivePosition() const;

            virtual void draw() const = 0;

            virtual void handle(const SDL_Event &e);
            virtual void step(); // method where each component updates itself
            
            void addEventListener(int eventType, EventListener* l);
        private:
            int x, y;
            int rPad = 0, lPad = 0, tPad = 0, bPad = 0;

            std::map<int, EventListener*> eventListeners;
    };
}

#endif /* INCLUDE_COMPONENT_HPP_HEADER_GUARD_258033191213708 */
