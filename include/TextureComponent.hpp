#ifndef INCLUDE_TEXTURECOMPONENT_HPP_HEADER_GUARD_32240110372870
#define INCLUDE_TEXTURECOMPONENT_HPP_HEADER_GUARD_32240110372870

#include "Component.hpp"
#include "Texture.hpp"

namespace sdlbox {
    // wrapper component for texture
    class TextureComponent : public Component {
        public:
            using Component::withPosition;

            ~TextureComponent();
            int getWidth() const override;
            int getHeight() const override;
            
            void draw() const override;

            void commit() override;
        protected:
            void setTexture(Texture* t);
            void repositionTexture(int xOffset, int yOffset);
        private:
            Texture* texture = NULL;
    };
}

#endif /* INCLUDE_TEXTURECOMPONENT_HPP_HEADER_GUARD_32240110372870 */
