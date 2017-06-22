#ifndef INCLUDE_GRAPHICSHELPER_HPP_HEADER_GUARD_28596195061331
#define INCLUDE_GRAPHICSHELPER_HPP_HEADER_GUARD_28596195061331

#include <SDL2/SDL.h>
#include "Texture.hpp"
#include "Font.hpp"
#include "Color.hpp"
#include <map>

namespace sdlbox {
    // contains nifty little static helper methods
    class GraphicsHelper {
        public:
            static void drawRect(SDL_Rect* where, const Color &color, bool fill=true);
            static void drawRoundedRect(SDL_Rect* where, int radius, const Color &color);
            static void drawCircle(int x0, int y0, int radius, const Color &color, int linewidth=1, int fillDirection=-1);
            static void drawEllipse(SDL_Rect* where, const Color &color, int linewidth=1, int fillDirection=-1);
            static void drawArc(int x0, int y0, int radius, double fromAngle, double toAngle, const Color &color);
            static Texture* createTexture(SDL_Surface* surf, bool freesrc=true);
            static Font* getDefaultFont(int size = 20); // pointer because copying fonts is scary
            static std::string getDefaultFontName();
            static Font* tryLoadFont(const std::string &fontFilename, int size = 20);
            static void freeLoadedFonts();
        private:
            static std::map<std::string, Font*> loadedFonts;
            static std::string defaultFont;
            static SDL_Color backup;

            static void setColor(SDL_Renderer* renderer, const Color &color); // save old color
            static void restoreColor(SDL_Renderer*); // restore color to old color

            static void equationEllipse(SDL_Renderer* renderer, int x0, int y0, int a, int b, int linewidth, int fillDirection);
            static void midpointEllipse(SDL_Renderer* renderer, int x0, int y0, int a, int b);
    };
}

#endif /* INCLUDE_GRAPHICSHELPER_HPP_HEADER_GUARD_28596195061331 */
