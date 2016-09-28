#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>


namespace GUI {

    class Component: public sf::Drawable, public sf::Transformable, private sf::NonCopyable
    {
    public:
        typedef std::shared_ptr<Component> pointer_type;

    public:
        Component();
        virtual ~Component();

        virtual bool isSelectable() const = 0;
        bool isSelected() const;
        virtual void select();
        virtual void deselect();

        virtual bool isActive() const;
        virtual void activate();
        virtual void deactivate();

        virtual void handleEvent(const sf::Event& event) = 0;

    private:
        bool _isSelected;
        bool _isActive;

    };

}


#endif//__COMPONENT_H__
