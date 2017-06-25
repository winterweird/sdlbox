#include "sdlbox.hpp"
#include <iostream>
#include <algorithm> // std::min

using namespace std;
using namespace sdlbox;

class Runner : public Component {
    public:
        Runner(int x, int y) {
            ComponentFactory(this).position(x, y);
        }

        int getWidth() const override {
            return 20;
        }
        int getHeight() const override {
            return 40;
        }
        void draw() const override {
            auto r = this->getRect();
            GraphicsHelper::drawRect(&r, Color(0, 255, 0));
        }

        void step() override {
            double goalX = getX(), goalY = getY();
            
            const Uint8* keys = SDL_GetKeyboardState(NULL);
            if (keys[SDL_SCANCODE_W]) {
                if (grounded) {
                    vspeed = -10;
                    grounded = false;
                    cout << "changed to ungrounded! " << vspeed << endl;
                }
            }
            if (keys[SDL_SCANCODE_S]) {
                if (grounded) {
                    cout << "hey" << endl;
                }
            }
            if (keys[SDL_SCANCODE_A]) {
                goalX = getX() - hspeed;
            }
            if (keys[SDL_SCANCODE_D]) {
                goalX = getX() + hspeed;
            }
            
            if (!grounded) {
                // update y position
                // On a side note, magic numbers are bad, and 250 is where the
                // "floor" is (or, 250 + height, really)
                double goalY = min(250.0, getY() + vOvershoot + vspeed);
                cout << "goalY is now " << goalY << endl;
                cout << "this is the result of " << getY() << " + " << vOvershoot << " + " << vspeed << endl;
                vOvershoot =  goalY - (int)round(goalY);
                
                if (goalY == 250.0) {
                    grounded = true;
                    vspeed = 0;
                    vOvershoot = 0;
                }
                else {
                    vspeed += gravity;
                }

            }
            
            ComponentFactory(this).position((int)round(goalX), (int)round(goalY));
            cout << "new pos: " << getX() << ", " << getY() << endl;
        }
    private:
        // NOTE: naïve approach to positioning and speed. What I used in Flappy
        // Bird was better (but more complicated, and I'm not trying to prove
        // anything right now).
        // I could also build a "PrecisePositionComponent" into the library,
        // anticipating that working with double positions will be a common use
        // case, and work with doubles behind the scenes. Exactly how
        // repositioning will happen might prove a challenge given my current
        // ComponentFactory approach, though, unless I include a separate API
        // for updating positions and such and use that instead. All in all, it
        // seems complicated, and generally easier to do this on a case-by-case
        // basis unless otherwise proven. (Although this might also be me
        // refusing to acknowledge a weakness in my design, I confess.)
        //
        // I really need to stop writing novels in comments concerning single
        // variable declarations.
        static const int hspeed = 2;
        constexpr static const double gravity = 0.2;
        double vOvershoot = 0;
        bool grounded = true;
        double vspeed = 0;
};

int main(int argc, char** argv) {
    SDLBox window("Side scroller - first attempt", 800, 300);

    window.addQuitButton(SDLK_ESCAPE, 0);

    Runner* runner = new Runner(200, 250);

    window.add(runner);

    mainloop(&window);

    return 0;
}
