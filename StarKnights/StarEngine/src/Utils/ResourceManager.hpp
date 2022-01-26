#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

#include <iostream>

namespace utils
{
    template <typename T>
    class ResourcesManager
    {
    public:
        std::shared_ptr<T> resourceForName(std::string name, const std::function<sp<T>(void)>& resourceCreator) const;
        template <typename FUN> void forEach(FUN fun);
        void clear() const;

    private:
        mutable std::unordered_map<std::string, std::shared_ptr<T>> _resources;
    };


    template<typename T>
    std::shared_ptr<T>
        ResourcesManager<T>::resourceForName(std::string name, const std::function<std::shared_ptr<T>(void)>& resourceCreator) const
    {
        std::shared_ptr<T> el;

        auto it = _resources.find(name);

        if (it == std::end(_resources))
        {
            std::cout << "Create [" << name << std::endl;
            el = resourceCreator();
            _resources[name] = el;
            std::cout << "]" << name << " end" << std::endl;
        }
        else
        {
            el = it->second;
        }

        return el;
    }


    template<typename T>
    void ResourcesManager<T>::clear() const
    {
        auto it = _resources.begin();
        while (it != _resources.end())
        {
            if (it->second->refCount() == 1)
            {
                std::cout << "Remove " << it->first << std::endl;
                it = _resources.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }


    template<typename T>
    template<typename FUN>
    void ResourcesManager<T>::forEach(FUN fun)
    {
        for (const auto& res : _resources)
        {
            fun(res.second);
        }
    }
}
#endif RESOURCE_MANAGER_HPP
