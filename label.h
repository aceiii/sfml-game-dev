#ifndef __LABEL_H__
#define __LABEL_H__

#include <SFML/Graphics/RenderTarget.hpp>
#include "fontholder.h"
#include "component.h"


namespace GUI
{
    class Label: public GUI::Component
    {
    public:
        Label(const std::string& text, const FontHolder& fonts);

        virtual bool isSelectable() const;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void setText(const std::string& text);

    private:
        sf::Text _text;

    };
}


#endif//__LABEL_H__

