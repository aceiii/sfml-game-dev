#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <functional>

#include "component.h"
#include "textureholder.h"
#include "fontholder.h"


namespace GUI
{
    class Button : public GUI::Component {
    public:
        Button(const FontHolder &fonts, const TextureHolder &textures);

        virtual ~Button();

        virtual bool isSelectable() const;
        virtual void select();
        virtual void deselect();

        virtual void activate();
        virtual void deactivate();

    private:
        sf::Texture _normalTexture;
        sf::Texture _selectedTexture;
        sf::Texture _pressedTexture;

        sf::Sprite _sprite;
        sf::Text _text;

        bool _isToggle;

        std::function<void()> _callback;

    };
}


#endif//__BUTTON_H__
