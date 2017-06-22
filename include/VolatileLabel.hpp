#ifndef INCLUDE_VOLATILELABEL_HPP_HEADER_GUARD_49382454119909
#define INCLUDE_VOLATILELABEL_HPP_HEADER_GUARD_49382454119909

#include "Label.hpp"

namespace sdlbox {
    class VolatileLabel : public Label {
        public:
            using Textual::setText;
            VolatileLabel(std::string text);
            VolatileLabel(std::string text, const Color & color);
            VolatileLabel(std::string text, const Color &fg, const Color &bg);

            // can't use Texture from base class
            int getWidth() const override;
            int getHeight() const override;

            void draw() const override;
        protected:
            void setText(const std::string &font, int size, const std::string &text, Color* fg, Color* bg, bool blended) override;
        private:
    };
}

#endif /* INCLUDE_VOLATILELABEL_HPP_HEADER_GUARD_49382454119909 */
