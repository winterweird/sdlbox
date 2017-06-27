#ifndef INCLUDE_COMPONENT_HPP_HEADER_GUARD_258033191213708
#define INCLUDE_COMPONENT_HPP_HEADER_GUARD_258033191213708

#include <SDL2/SDL.h>
#include <map>
#include <mutex>
#include <vector>
#include <condition_variable>
#include "EventListener.hpp"
#include "Layout.hpp" 
namespace sdlbox {
    extern std::mutex mtx;
    extern std::condition_variable cv;
    extern bool isDrawing;
    
    class Component {
        friend class ComponentFactory;
        public:
            virtual ~Component();
            
            virtual int getWidth() const = 0;
            virtual int getHeight() const = 0;

            virtual int getX() const;
            virtual int getY() const;

            SDL_Rect getRect() const;

            virtual bool collidable() const;
            virtual bool collides(Component* c) const; // check collision with other component

            [[deprecated]]
            virtual Component* withPosition(int x, int y, int anchor=Layout::TOPLEFT);
            [[deprecated]]
            virtual Component* withPosition(Component* relative, int x, int y,
                    int anchor=Layout::TOPLEFT);

            [[deprecated]]
            virtual Component* withReceivePosition(bool val);

            int getVerticalPadding() const;
            int getHorizontalPadding() const;
            int getLeftPadding() const;
            int getRightPadding() const;
            int getTopPadding() const;
            int getBottomPadding() const;
            void getPadding(int &lPad, int &rPad, int &tPad, int &bPad) const;

            int getZLevel() const;

            // add padding
            [[deprecated]]
            virtual Component* withVPad(int amount); // vertical (top + bottom)
            [[deprecated]]
            virtual Component* withHPad(int amount); // horizontal (left + right)
            [[deprecated]]
            virtual Component* withLPad(int amount); // left
            [[deprecated]]
            virtual Component* withRPad(int amount); // right
            [[deprecated]]
            virtual Component* withTPad(int amount); // top
            [[deprecated]]
            virtual Component* withBPad(int amount); // bottom
            [[deprecated]]
            virtual Component* withPadding(int vPad, int hPad);
            [[deprecated]]
            virtual Component* withPadding(int lPad, int rPad, int tPad, int bPad);

            // whether or not the specified component should receive its
            // position from its parent or not
            virtual bool receivePosition() const;

            virtual void draw() const = 0;

            virtual void handle(const SDL_Event &e);
            virtual void step(); // method where each component updates itself

            // propagate information added to base class down the subclasses
            virtual void commit();
            
            void addEventListener(int eventType, EventListener* l);
            void clearEventListeners(int eventType); // delete all listeners of a given type

            virtual bool operator<(Component* other) const; // order by Z level and otherwise determine draw order
            virtual bool drawable() const;
        private:
            double x, y;
            int rPad = 0, lPad = 0, tPad = 0, bPad = 0;
            int zlvl = 0;
            bool rcvPos = true;

            std::map<int, std::vector<EventListener*> > eventListeners;
    };
}

#endif /* INCLUDE_COMPONENT_HPP_HEADER_GUARD_258033191213708 */
