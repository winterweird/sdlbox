#include "sdlbox.hpp"
#include <iostream>
#include <algorithm> // std::min

using namespace std;
using namespace sdlbox;

class GameObject : public Component {
    public:
        GameObject(int x, int y, const Color &color, double vSpeed, double hSpeed) : color(color), vSpeed(vSpeed), hSpeed(hSpeed) {
            ComponentFactory(this).position(x, y);
        }

        void draw() const override {
            auto r = this->getRect();
            GraphicsHelper::drawRect(&r, color);
        }

        bool collidable() const override {
            return true;
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

        double getHSpeed() const {
            return hSpeed;
        }

        double getVSpeed() const {
            return vSpeed;
        }
        
    private:
        Color color;

        double vSpeed, hSpeed; // init from subclass constr
};

class Runner : public GameObject {
    public:
        Runner(int x, int y) : GameObject(x, y, Color(0, 255, 0), 0, 0) {
            addEventListener(UserEvents::existingEventCode("COLLISION_EVENT"),
                    new EventListener([this](const SDL_Event &e) {
                        return e.user.data1 == this || e.user.data2 == this;
                    }, [](const SDL_Event &e) {
                        SDLBox::getInstance()->goToRoom(Room("GameOverScreen"));
                    }));
        }

        int getWidth() const override {
            return 20;
        }
        int getHeight() const override {
            return 40;
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

            ComponentFactory cf(this);
            cf.updateX(getHSpeed(), 0, 800-getWidth());
            cf.updateY(getVSpeed(), 0, 250, [this]{
                this->grounded = true;
                this->vAccel(0);
            });
        }
    private:
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
            ComponentFactory(this).updateX(getHSpeed(), 0-getWidth(), 800 + 100, [this]{
                SDLBox::getInstance()->scheduleDestruct(this);
            });
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

    Rooms::addRoom("GameScreen");
    Rooms::addRoom("GameOverScreen");
    
    window.addQuitButton(SDLK_ESCAPE, 0);

    window.goToRoom(Room("GameOverScreen"));
    window.add(ComponentFactory(new Label("GAME OVER"))
            .position(window.getWidth()/2.0, window.getHeight()/2.0, Layout::CENTER)
            .create());
    window.add(ComponentFactory(new Label("(Press space to try again)"))
            .position(window.getWidth()/2.0, window.getHeight()/2.0 + 30, Layout::CENTER)
            .create());

    auto newGame = [&](const SDL_Event &e) {
        window.goToRoom(Room("GameScreen"));
        window.wipe();
        
        Runner* runner = new Runner(200, 250);
        window.add(runner);
        
        window.add(new ObstacleSpawner(840, 0));
    };

    window.addEventListener(SDL_KEYDOWN,
            new EventListener([&](const SDL_Event &e){
                return window.getActiveRoom() == "GameOverScreen" && e.key.keysym.sym == SDLK_SPACE;
            }, newGame));

    newGame(SDL_Event());

    mainloop(&window);
    
    return 0;
}
