#ifndef INCLUDE_LABEL_HPP_HEADER_GUARD_145122513912977
#define INCLUDE_LABEL_HPP_HEADER_GUARD_145122513912977

#include "Textual.hpp"

namespace sdlbox {
    class Label : public Textual {
        public:
            using Textual::setText;
            
            Label(std::string text, bool blended=false); // creates black text
            Label(std::string text, const Color &color, bool blended=false);
            Label(std::string text, const Color &fgColor, const Color &bgColor); // shaded text
            
//            void commit() override;
        protected:
            void setText(const std::string &font, int size, const std::string &text, Color* fg, Color* bg, bool blended) override;
        private:
    };
}

#endif /* INCLUDE_LABEL_HPP_HEADER_GUARD_145122513912977 */
