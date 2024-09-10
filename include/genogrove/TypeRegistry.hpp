#ifndef GENOGROVE_TYPEREGISTRY_HPP
#define GENOGROVE_TYPEREGISTRY_HPP

// Standard
#include <string>
#include <unordered_map>
#include <typeindex>
#include <stdexcept>
#include <any>
#include <iostream>
#include <functional>
#include <typeinfo>
#include <memory>

// Class
#include "AnyType.hpp"
#include "TypedData.hpp"

namespace genogrove {
    class AnyBase;

    using castFunction = std::function<std::any(const std::shared_ptr<AnyBase>&)>;

    class TypeRegistry {
    public:
        static TypeRegistry &instance() {
            static TypeRegistry instance;
            return instance;
        }

        TypeRegistry(const TypeRegistry &) = delete;
        TypeRegistry &operator=(const TypeRegistry &) = delete;

        template<typename T>
        static void registerType(std::string typeName) {
            typeNames[typeid(T)] = typeName; // store the type name
            std::type_index typeIndex = typeid(T);
            if (castFunctions.find(typeIndex) == castFunctions.end()) {
                castFunctions[typeIndex] = [](const std::shared_ptr<AnyBase>& obj) -> TypedData<T> {
                    auto castedObj = std::dynamic_pointer_cast<
                            AnyType<typename std::remove_reference<T>::type>>(obj);
                    if(!castedObj) {
                        std::cerr << "Failed to cast object to type " << typeid(T).name() << std::endl;
                    }
                    return castedObj->getData();
                };
            }
        }
//        static std::any cast(const std::shared_ptr<AnyBase>& obj, std::type_index typeIndex);

    private:
        TypeRegistry() = default;
        static std::unordered_map<std::type_index, std::string> typeNames;
        static std::unordered_map<std::type_index, castFunction> castFunctions;
    };
}

#endif //GENOGROVE_TYPEREGISTRY_HPP
