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

    private:
        bool hasSelection();
        void selectNext();
        void selectPrevious();

    private:
        std::vector<GUI::Component::pointer_type> _children;
        int _selectedChild;

    };

}


#endif//__CONTAINER_H__

