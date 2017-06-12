#include "sdlbox.hpp"
#include <iostream>

using namespace sdlbox;
using namespace std;

int main(int argc, char** argv) {
    SDLBox window("Window title");

    window.setOrientation(Layout::HORIZONTAL);

    class C : public Callback {
        public:
            void callback() override {
                cout << "Why hello there!" << endl;
            }
    };
    
    window.add(new Label("Here is some text to make sure stuff works"));
    window.add((new Button("Button text", new C))->withHPad(20));
    window.add(new Label("And here is some more text"));
    mainloop(&window);

    return 0;
}
