//
// Created by Gabriel on 5/19/2025.
//

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <memory>
#include <unordered_map>
#include <string>
#include "../Entities/Animation.h"
#include <stdexcept>
template <typename T>

class ResourceManager {
    inline static std::unordered_map<std::string, std::shared_ptr<T>> resources;
public:
    template<typename... Args>
    std::shared_ptr<T> load(const std::string &name, Args&&... args){
        auto it = resources.find(name);
        if (it != resources.end()) {
            return it->second;
        }
        auto res = std::make_shared<T>(std::forward<Args>(args)...);
        resources[name] = res;
        return res;
    }

    std::shared_ptr<T> get(const std::string &name){
        if (resources.find(name) == resources.end()) {
            throw std::runtime_error("Resource " + name + " not found");
        }
        return resources[name];
    }
};



#endif //RESOURCEMANAGER_H
