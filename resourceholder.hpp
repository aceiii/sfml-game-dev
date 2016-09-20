#ifndef __RESOURCE_HOLDER_IMPL_H__
#define __RESOURCE_HOLDER_IMPL_H__

#include <cassert>


template <typename R, typename I>
void ResourceHolder<R, I>::load(I id, const std::string& filename) {
    std::unique_ptr<R> resource(new R());
    if (!resource->loadFromFile(filename)) {
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    }

    auto inserted = _resourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

template <typename R, typename I>
template <typename P>
void ResourceHolder<R, I>::load(I id, const std::string& filename, const P& secondParam) {
    std::unique_ptr<R> resource(new R());
    if (!resource->loadFromFile(filename, secondParam)) {
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    }

    auto inserted = _resourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

template <typename R, typename I>
R& ResourceHolder<R, I>::get(I id) {
    auto found = _resourceMap.find(id);
    assert(found != _resourceMap.end());

    return *found->second;
}

template <typename R, typename I>
const R& ResourceHolder<R, I>::get(I id) const {
    auto found = _resourceMap.find(id);
    assert(found != _resourceMap.end());

    return *found->second;
}


#endif//__RESOURCE_HOLDER_IMPL_H__
