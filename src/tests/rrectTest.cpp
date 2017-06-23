#include "sdlbox.hpp"
#include <iostream>

using namespace sdlbox;
using namespace std;

class TestClass : public Component {
    public:
        int getWidth() const override {
            return 100;
        }
        int getHeight() const override {
            return 40;
        }

        int getX() const override {
            return 20;
        }
        int getY() const override {
            return 20;
        }
        
        void draw() const override {
            SDL_Rect r;
            r.x = getX();
            r.y = getY();
            r.w = getWidth();
            r.h = getHeight();
            GraphicsHelper::drawRoundedRect(&r, 20, Color(0,0,0));
        }
};

int main(int argc, char** argv) {
    SDLBox window("Window title", 640, 480);

    window.add(new TestClass);
    
    mainloop(&window);

    return 0;
}
