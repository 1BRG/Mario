//
// Created by Gabriel on 5/19/2025.
//

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <memory>
#include <unordered_map>
#include <string>
#include <stdexcept>

// Template class for managing reusable resources of type T
template <typename T>
class ResourceManager {
    inline static std::unordered_map<std::string, std::shared_ptr<T>> resources; // Storage for loaded resources
public:
    // Load a resource with given name and constructor arguments if not already loaded
    template<typename... Args>
    std::shared_ptr<T> load(const std::string &name, Args&&... args) {
        auto it = resources.find(name);
        if (it != resources.end()) {
            return it->second;           // Return existing resource
        }
        auto res = std::make_shared<T>(std::forward<Args>(args)...); // Create new resource
        resources[name] = res;         // Store for future use
        return res;
    }

    // Retrieve a previously loaded resource by name
    std::shared_ptr<T> get(const std::string &name) {
        if (resources.find(name) == resources.end()) {
            throw std::runtime_error("Resource " + name + " not found");
        }
        return resources[name];         // Return shared pointer to resource
    }
};

#endif //RESOURCEMANAGER_H