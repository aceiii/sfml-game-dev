#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <vector>

#include "component.h"


namespace GUI
{
    class Container: public GUI::Component
    {
    public:
        Container();
        ~Container();

        virtual bool isSelectable() const;
        virtual void select(std::size_t index);

        virtual void handleEvent(const sf::Event& event);

        void pack(GUI::Component::pointer_type component);

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        bool hasSelection();
        void selectNext();
        void selectPrevious();

    private:
        std::vector<GUI::Component::pointer_type> _children;
        std::size_t _selectedChild;

    };

}


#endif//__CONTAINER_H__

