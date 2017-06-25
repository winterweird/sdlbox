#include "sdlbox.hpp"
#include <iostream>

using namespace sdlbox;
using namespace std;

class Bird : public Component {
    public:
        Bird(double x, double y, double* gravity) : x(x), y(y), gravity(gravity) {
            if (instance != NULL) {
                throw runtime_error("Only one bird allowed at a time!"); }
            instance = this; 
            addEventListener(SDL_KEYDOWN, new EventListener([this](const SDL_Event &e) {
                if (e.key.keysym.sym == SDLK_SPACE && !justjumped) {
                    justjumped = true;
                    vspeed = -jumpBoost;
                }
            }));
            addEventListener(SDL_KEYUP, new EventListener([this](const SDL_Event &e) {
                if (e.key.keysym.sym == SDLK_SPACE) {
                    justjumped = false;
                }
            }));
        }

        ~Bird() {
            instance = NULL;
        }

        static Bird* getInstance() {
            return instance;
        }
        
        int getX() const override {
            return x;
        }
        int getY() const override {
            return (int)round(y);
        }
        int getWidth() const override {
            return (int)round(width);
        }
        int getHeight() const override {
            return height;
        }
        
        void draw() const override {
            SDL_Rect area; area.w = width;
            area.h = height;
            area.x = x;
            area.y = y;
            GraphicsHelper::drawRect(&area, Color(255,0,0));
        }
        
        void step() override {
            vspeed += *gravity;
            y += vspeed;
            
            auto win = SDLBox::getInstance();

            if (y >= win->getHeight() || y <= -getHeight()) {
                SDL_Event e;
                e.type = UserEvents::existingEventCode("GameOverEvent");
                SDL_PushEvent(&e);
            }
        }
    private:
        double x, y;
        const int width = 30;
        const int height = 30;
        double jumpBoost = 7.0;
        double vspeed = -jumpBoost;
        double* gravity; // pointer to global gravity var
        bool justjumped = false;
        static Bird* instance;
};

Bird* Bird::instance = NULL;

class Pillar : public Component {
    public:
        Pillar(int x, int height, bool ground) : x(x), height(height), standingOnGround(ground) {}
        
        int getX() const override {
            return (int)round(x);
        }
        int getY() const override {
            if (standingOnGround) {
                return SDLBox::getInstance()->getHeight() - height;
            }
            return 0; // starts from top
        }
        int getWidth() const override {
            return width;
        }
        int getHeight() const override {
            return height;
        }
        
        void draw() const override {
            SDL_Rect area;
            area.w = getWidth();
            area.h = getHeight();
            area.x = getX();
            area.y = getY();
            GraphicsHelper::drawRect(&area, Color(0, 255, 0));
        }
        
        void step() override {
            if (x + width < 0) {
                SDLBox::getInstance()->scheduleDestruct(this);
            }
            else {
                x -= hspeed;
            }
            
            Bird* bird = Bird::getInstance();
            SDL_Event e;
            
            if (bird->collides(this)) {
                e.type = UserEvents::existingEventCode("GameOverEvent");
                SDL_PushEvent(&e);
            }
            else if (bird->getX() > getX() + getWidth() && standingOnGround && !hasBeenPassed) {
                // standingOnGround: ensure that only one of the two pillars
                // registers an increase in score
                e.type = UserEvents::existingEventCode("ScoreIncrementEvent");
                SDL_PushEvent(&e);
                hasBeenPassed = true;
            }
        }
    private:
        double x;
        static const int width = 50;
        int height;
        bool standingOnGround;
        bool hasBeenPassed = false;
        static double hspeed; // class constant
};

double Pillar::hspeed = 3.0; // init pillar horizontal speed

class PillarSpawnPoint : public Component {
    public:
        PillarSpawnPoint(double x, int mgz, int mh) : x(x), minGapSize(mgz), minHeight(mh) {
            if (2*minHeight + minGapSize > SDLBox::getInstance()->getHeight()) {
                throw runtime_error("Window too small to support given height/gap size");
            }
        }
        int getX() const override {
            return (int)round(x);
        }
        int getY() const override {
            return -1; // n/a
        }
        int getWidth() const override {
            return -1; // n/a
        }
        int getHeight() const override {
            return -1; // n/a
        }

        void draw() const override {
            // n/a
        }

        void step() override {
            // a
            if (--countdown <= 0) {
                auto win = SDLBox::getInstance();
                int winHeight = win->getHeight();
                int gapSize = win->randint(minGapSize, winHeight-2*minHeight);
                int gapPos = win->randint(minHeight, winHeight-minHeight-gapSize);
                win->add(new Pillar(x, gapPos, false));
                win->add(new Pillar(x, winHeight-(gapPos+gapSize), true));
                countdown = win->randint(minCountdown, minCountdown + countdownVariance);
            }
        }
    private:
        double x;
        int minGapSize;
        int minHeight;
        int countdown = 0;
        static const int minCountdown = 80;
        static const int countdownVariance = 40;
};

int main(int argc, char** argv) {
    SDLBox window("Flappy bird!", 640, 480);

    // set up event codes (this is not strictly necessary)
    UserEvents::eventCode("GameOverEvent");
    UserEvents::eventCode("RestartGameEvent");
    UserEvents::eventCode("ScoreIncrementEvent");

    // add rooms (this is)
    Rooms::addRoom("Game");
    Rooms::addRoom("Game Over");
    
    // setup game over screen
    window.goToRoom(Room("Game Over"));

    window.add(ComponentFactory(new Label("GAME OVER"))
            .position(320, 240, Layout::CENTER)
            .create());
    window.add(ComponentFactory(new Label("(Press space to play again)"))
            .position(320, 270, Layout::CENTER)
            .create());
    
    window.addEventListener(UserEvents::existingEventCode("GameOverEvent"),
            new EventListener([&](const SDL_Event &e) {
                return window.getActiveRoom() == "Game";
            }, [&](const SDL_Event &e) {
                window.goToRoom(Room("Game Over"));
            }));
    
    window.addQuitButton(SDLK_w, KMOD_CTRL);
    window.addQuitButton(SDLK_ESCAPE, 0);
    
    double gravity = 0.2;
    int score;

    auto initGame = [&](const SDL_Event &e) {
        window.goToRoom(Room("Game"));
        window.wipe();

        Bird* birb = new Bird(300, 200, &gravity);
        window.add(birb);
        
        window.add(new PillarSpawnPoint(window.getWidth() + 10, 100, 50));

        score = 0;

        Label* lab = (Label*)ComponentFactory(new Label("Score: 0"))
            .position(620, 20, Layout::TOPRIGHT)
            .create();
        
        auto onScore = [&, lab](const SDL_Event &e) {
            lab->setText("Score: " + to_string(++score));
        };
        lab->addEventListener(UserEvents::existingEventCode("ScoreIncrementEvent"), new EventListener(onScore));
        
        window.add(lab);
    };

    window.addEventListener(UserEvents::existingEventCode("RestartGameEvent"),
            new EventListener(initGame));
    
    window.addEventListener(SDL_KEYDOWN, new EventListener([&](const SDL_Event &e) {
        return window.getActiveRoom() == "Game Over" && e.key.keysym.sym == SDLK_SPACE;
    }, [&](const SDL_Event &e) {
        SDL_Event ev;
        if (window.getActiveRoom() == "Game Over" && e.key.keysym.sym == SDLK_SPACE) {
            ev.type = UserEvents::existingEventCode("RestartGameEvent");
            SDL_PushEvent(&ev);
        }
    }));
    
    initGame(SDL_Event());

    mainloop(&window);
    return 0;
}
