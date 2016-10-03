#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <functional>

#include "component.h"
#include "textureholder.h"
#include "fontholder.h"


namespace GUI
{
    class Button : public GUI::Component
    {
    public:
        typedef std::function<void()> function;

    public:
        Button(const FontHolder &fonts, const TextureHolder &textures);

        virtual ~Button();

        virtual bool isSelectable() const;
        virtual void select();
        virtual void deselect();

        virtual void activate();
        virtual void deactivate();

        virtual void handleEvent(const sf::Event& event);

        void setText(const std::string& text);
        void setCallback(function func);
        void setToggle(bool toggle);

    protected:
        void draw(sf::RenderTarget& window, sf::RenderStates states) const;

    private:
        void updateText();

    private:
        const sf::Texture& _normalTexture;
        const sf::Texture& _selectedTexture;
        const sf::Texture& _pressedTexture;

        sf::Sprite _sprite;
        sf::Text _text;

        bool _isToggle;

        function _callback;

    };
}


#endif//__BUTTON_H__
