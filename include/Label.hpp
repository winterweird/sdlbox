#ifndef INCLUDE_LABEL_HPP_HEADER_GUARD_145122513912977
#define INCLUDE_LABEL_HPP_HEADER_GUARD_145122513912977

#include "Component.hpp"
#include <string>
#include "Color.hpp"
#include "Texture.hpp"

namespace sdlbox {
    class Label : public Component {
        public:
            Label(std::string text, bool blended=false); // creates black text
            Label(std::string text, Color color, bool blended=false);
            Label(std::string text, Color fgColor, Color bgColor); // shaded text

            int getWidth() const override;
            int getHeight() const override;

            // custom setPosition methods which also sets the position of the
            // underlying Texture
            void setPosition(int x, int y) override;
            void setPosition(Component* relative, int x, int y) override;

            void draw() const override;
        private:
            Texture* texture;
    };
}

#endif /* INCLUDE_LABEL_HPP_HEADER_GUARD_145122513912977 */
