#include "sdlbox.hpp"
#include <iostream>

using namespace sdlbox;
using namespace std;

class Shape : public Component {
    public:
        Shape(int x, int y) {
            this->x = x;
            this->y = y;
        }

        int getX() const override {
            return x;
        }

        int getY() const override {
            return y;
        }
    protected:
        int x, y;
};

class Ellipse : public Shape {
    public:
        Ellipse(int x, int y, int w, int h, const Color &color, int linewidth=1) : Shape(x, y), color(color) {
            this->w = w;
            this->h = h;
            this->linewidth = linewidth;
        }

        void draw() const override {
            SDL_Rect r;
            r.x = getX();
            r.y = getY();
            r.w = getWidth();
            r.h = getHeight();
            GraphicsHelper::drawEllipse(&r, color, linewidth);
        }

        int getWidth() const override {
            return w;
        }

        int getHeight() const override {
            return h;
        }
    private:
        Color color;
        int w, h;
        int linewidth;
};

class Circle : public Shape {
    public:
        Circle(int x, int y, int radius, const Color &color, int lineWidth = 1) : Shape(x-radius, y-radius), color(0,0,0) {
            this->radius = radius;
            this->color = color;
            this->linewidth = lineWidth;
        }
        
        void draw() const override {
            GraphicsHelper::drawCircle(getX() + radius, getY() + radius, radius, color, linewidth);
        }

        int getWidth() const override {
            return radius * 2;
        }

        int getHeight() const override {
            return radius * 2;
        }
    protected:
        int radius;
        int linewidth;
    private:
        Color color;
};

class ChangeableCircle : public Circle {
    public:
        ChangeableCircle(int x, int y, int radius, const Color &color, int lineWidth = 1) : Circle(x, y, radius, color, lineWidth) {}

        void increaseRadius() {
            if (radius < 100) radius++;
            linewidth = min(radius*2, linewidth);
        }
        void decreaseRadius() {
            if (radius > 10) radius--;
            linewidth = min(radius*2, linewidth);
        }
        void increaseLinewidth() {
            if (linewidth < radius*2) linewidth++;
        }
        void decreaseLinewidth() {
            if (linewidth > 1) linewidth--;
        }
        void moveLeft() {
            if (x > 0) x -= 5;
        }
        void moveRight() {
            if (x + 2*radius < 640) x += 5;
        }
        void moveUp() {
            if (y > 0) y -= 5;
        }
        void moveDown() {
            if (y + 2*radius < 480) y += 5;
        }

        void step() override {
            const Uint8* keys = SDL_GetKeyboardState(NULL);
            if (keys[SDL_SCANCODE_UP]) {
                moveUp();
            }
            if (keys[SDL_SCANCODE_DOWN]) {
                moveDown();
            }
            if (keys[SDL_SCANCODE_LEFT]) {
                moveLeft();
            }
            if (keys[SDL_SCANCODE_RIGHT]) {
                moveRight();
            }
        }
    private:
};

int main(int argc, char** argv) {
    SDLBox window("Testing drawing shapes", 640, 480);
    
    window.add(new Circle(300, 150, 80, Color(255, 0, 255), 49));
    window.add(new Circle(200, 200, 50, Color(0,0,0)));
    window.add(new Ellipse(200, 200, 200, 100, Color(0, 255, 0)));
    window.add(new Ellipse(200, 200, 200, 100, Color(0, 0, 255), 20));

    auto changeableCircle = new ChangeableCircle(100, 100, 50, Color(0, 255, 255), 10);
    changeableCircle->addEventListener(SDL_KEYDOWN, new EventListener([&](const SDL_Event &e) {
        if (e.key.keysym.sym == SDLK_w)
            changeableCircle->increaseRadius();
        else if (e.key.keysym.sym == SDLK_s)
            changeableCircle->decreaseRadius();
        else if (e.key.keysym.sym == SDLK_d)
            changeableCircle->increaseLinewidth();
        else if (e.key.keysym.sym == SDLK_a)
            changeableCircle->decreaseLinewidth();
    }));
    window.add(changeableCircle);

    window.ctrlWToQuit();
    
    mainloop(&window);
    return 0;
}
