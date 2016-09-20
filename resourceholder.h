#ifndef __RESOURCE_HOLDER_H__
#define __RESOURCE_HOLDER_H__


#include <string>
#include <memory>

#include <SFML/Graphics.hpp>


template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
    void load(Identifier id, const std::string& filename);

    template <typename Parameter>
    void load(Identifier id, const std::string& filename, const Parameter& secondParam);

    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;

private:
    std::map<Identifier, std::unique_ptr<Resource>> _resourceMap;
};


#include "resourceholder.hpp"

#endif//__RESOURCE_HOLDER_H__
