#pragma once
#ifndef DEPENDENCY_INJECTION_H
#define DEPENDENCY_INJECTION_H

#include <functional>
#include <map>
#include <string>


class DIContainer {
public:
    template<typename T>
    void registerComponent(const std::string& name, T* component) {
        components[name] = [component]() { return component; };
    }

    template<typename T>
    T* getComponent(const std::string& name) {
        return static_cast<T*>(components[name]());
    }

private:
    std::map<std::string, std::function<void* ()>> components;
};

#endif // DEPENDENCY_INJECTION_H
