#include "sdlbox.hpp"
#include <iostream>

using namespace sdlbox;
using namespace std;

class Bird : public Component {
    public:
        Bird(double x, double y, double* gravity) : x(x), y(y), gravity(gravity) {
            if (instance != NULL) {
                throw runtime_error("Only one bird allowed at a time!");
            }
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
            SDL_Rect area;
            area.w = width;
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
            if (bird->collides(this)) {
                SDL_Event e;
                e.type = UserEvents::existingEventCode("GameOverEvent");
                SDL_PushEvent(&e);
            }
        }
    private:
        double x;
        static const int width = 50;
        int height;
        bool standingOnGround;
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

class Game : public SDLBox {
    public:
        Game() : SDLBox("Flappy bird!", 640, 480) { }
//            UserEvents::eventCode("GameOverEvent"); // set up event code
//
//            addEventListener(UserEvents::existingEventCode("GameOverEvent"),
//                    new EventListener([this](const SDL_Event &e) {
//                        goToRoom(Room::GAME_OVER);
//                    }));
//
//            initGameOverScreen();
//
//            goToRoom(Room::GAME);
//        }
//        ~Game() {
//            for (auto c : gameComponents) {
//                delete c;
//            }
//            for (auto c : gameOverComponents) {
//                delete c;
//            }
//            components.clear(); // avoid double delete in parent dtor
//        }
//    private:
//        double gravity = 0.2;
//
//        enum class Room {
//            GAME,
//            GAME_OVER
//        };
//
//        void goToRoom(Room room) {
//            switch(room) {
//                case Room::GAME:
//                    initGame();
//                    break;
//                case Room::GAME_OVER:
//                    destroyGame();
//                    components = gameOverComponents;
//                    break;
//            }
//
//            activeRoom = room;
//        }
//
//        void initGameOverScreen() {
//            Label* gameOver = new Label("GAME OVER");
//            gameOver->withPosition(getWidth()/2, getHeight()/2);
//            gameOverComponents.push_back(gameOver);
//        }
//
//        void initGame() {
//            Bird* birb = new Bird(300, 200, &gravity);
//            add(birb);
//
//            add(new PillarSpawnPoint(getWidth() + 10, 100, 50));
//        }
//
//        void destroyGame() {
//            if (activeRoom != Room::GAME) {
//                throw runtime_error("Illegal state: destroyGame called from game over screen");
//            }
//
//            for (auto c : components) {
//                delete c;
//            }
//            components.clear();
//        }
//
//        vector<Component*> gameComponents;
//        vector<Component*> gameOverComponents;
//
//        Room activeRoom;
};

int main(int argc, char** argv) {
    Game game;

    game.ctrlWToQuit();

    mainloop(&game);
    return 0;
}
