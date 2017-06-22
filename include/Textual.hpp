#ifndef INCLUDE_TEXTUAL_HPP_HEADER_GUARD_303021340728030
#define INCLUDE_TEXTUAL_HPP_HEADER_GUARD_303021340728030

#include "TextureComponent.hpp"
#include "Font.hpp"

namespace sdlbox {
    class Textual : public TextureComponent {
        public:
            ~Textual();
            virtual void setText(const std::string &text, bool blended=false);
            virtual void setText(const std::string &font, const std::string &text, bool blended=false);
            virtual void setText(const std::string &text, const Color &color, bool blended=false);
            virtual void setText(const std::string &font, const std::string &text, const Color &color, bool blended=false);
            virtual void setText(const std::string &text, const Color &fg, const Color &bg);
            virtual void setText(const std::string &font, const std::string &text, const Color &fg, const Color &bg);

            void setMessage(const std::string &message);
            void setFont(const std::string &font, int size=20, bool blended=false);
            void setForeground(Color* fg);
            void setBackground(Color* bg);

            std::string getMessage() const;
            std::string getFontName() const;
            Font* getFont() const;
            Color* getForeground() const;
            Color* getBackground() const;
            bool textIsBlended() const;

            Texture* createTexture() const;
        protected:
            void commit(); // use the text set previously to create a texture
            virtual void setText(const std::string &font, int size, const std::string &text, Color* fg, Color* bg, bool blended);
        private:
            std::string msg;
            std::string fontName;
            int fontSize;
            Color* fgColor = NULL;
            Color* bgColor = NULL;
            bool blended;
    };
}

#endif /* INCLUDE_TEXTUAL_HPP_HEADER_GUARD_303021340728030 */
