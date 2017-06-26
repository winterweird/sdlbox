#include "sdlbox.hpp"
#include <iostream>
#include <algorithm> // std::min

using namespace std;
using namespace sdlbox;

class GameObject : public Component {
    public:
        GameObject(int x, int y, const Color &color, double vSpeed, double hSpeed) : color(color), xPos(x), yPos(y), vSpeed(vSpeed), hSpeed(hSpeed) {
            ComponentFactory(this).position(x, y);
        }

        void draw() const override {
            auto r = this->getRect();
            GraphicsHelper::drawRect(&r, color);
        }

        void vAccel(double goal) {
            vSpeed = goal;
        }

        void vAccel(double goal, double amount) {
            if (goal > vSpeed)
                vSpeed = min(vSpeed + amount, goal);
            else
                vSpeed = max(vSpeed - amount, goal);
        }

        void hAccel(double goal) {
            hSpeed = goal;
        }

        void hAccel(double goal, double amount) {
            if (goal > hSpeed)
                hSpeed = min(hSpeed + amount, goal);
            else
                hSpeed = max(hSpeed - amount, goal);
        }

        virtual void cap() {}
        
        void cap(double minX, double maxX, double minY, double maxY) {
            xPos = max(minX, min(xPos, maxX));
            yPos = max(minY, min(yPos, maxY));
        }

        void step() override {
            // subclass behavior goes here
            
            // this might become troublesome
            xPos += hSpeed;
            yPos += vSpeed;

            cap();
            
            ComponentFactory(this).position(round(xPos), round(yPos));
        }
        
    private:
        Color color;

        double xPos, yPos; // keep track of actual position
        double vSpeed, hSpeed; // init from subclass constr
};

class Runner : public GameObject {
    public:
        Runner(int x, int y) : GameObject(x, y, Color(0, 255, 0), 0, 0) { }

        int getWidth() const override {
            return 20;
        }
        int getHeight() const override {
            return 40;
        }

        void cap() override {
            GameObject::cap(0, 800-getWidth(), 0, 250);
            
            if (getY() == 250) {
                grounded = true;
                vAccel(0);
            }
        }

        void step() override {
            hAccel(0); // reset hSpeed
            
            const Uint8* keys = SDL_GetKeyboardState(NULL);
            if (keys[SDL_SCANCODE_W]) {
                if (grounded) {
                    vAccel(-vspeedBoost);
                    grounded = false;
                }
            }
            if (keys[SDL_SCANCODE_S]) {
                if (grounded) {
                    // TODO: idk
                }
            }
            if (keys[SDL_SCANCODE_A]) {
                hAccel(-2, 2);
            }
            if (keys[SDL_SCANCODE_D]) {
                hAccel(2, 2);
            }
            
            if (!grounded) {
                // "100" is just some random big value
                vAccel(100, gravity);
            }

            GameObject::step();
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
        
        bool grounded = true;
        constexpr static const double vspeedBoost = 6.0;
};

class Obstacle : public GameObject {
    public:
        Obstacle(int x, int y, double hSpeed, int width, int height) : GameObject(x, y, Color(255, 0, 0), 0, -hSpeed), width(width), height(height) {}

        int getWidth() const override {
            return width;
        }

        int getHeight() const override {
            return height;
        }

        void step() override {
            GameObject::step();
            if (getX() < -getWidth()) {
                SDLBox::getInstance()->scheduleDestruct(this);
            }
        }
    private:
        int width, height;
};

class ObstacleSpawner : public Component {
    public:
        ObstacleSpawner(int x, int y) {
            ComponentFactory(this).position(x, y);
        }

        void step() override {
            if (--timer <= 0) {
                auto win = SDLBox::getInstance();
                int width = win->randint(20, 50);
                int height = win->randint(20, 40);
                int ypos = win->getHeight() - win->randint(minAboveBottom, maxAboveBottom) - height;
                int speed = win->randint(10, 30);
                win->add(new Obstacle(getX(), ypos, speed/10.0, width, height));
                timer = cooldown;
            }
        }

        int getWidth() const override {
            return -1; // N/A
        }
        int getHeight() const override {
            return -1; // N/A
        }
        void draw() const override { }

        bool drawable() const override {
            return false;
        }
    private:
        int timer = 0;
        const int cooldown = 100;
        const int maxAboveBottom = 100;
        const int minAboveBottom = 10;
};

int main(int argc, char** argv) {
    SDLBox window("Side scroller - first attempt", 800, 300);

    window.addQuitButton(SDLK_ESCAPE, 0);

    Runner* runner = new Runner(200, 250);

    window.add(runner);
    window.add(new ObstacleSpawner(840, 0));

    mainloop(&window);
    
    // I sorta lost touch with what I was doing...
    // TODO: figure that out.

    return 0;
}
