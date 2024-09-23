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
#include <stdexcept>

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
                castFunctions[typeIndex] = [](const std::shared_ptr<AnyBase>& obj) -> T {
                    auto castedObj = std::dynamic_pointer_cast<
                            AnyType<typename std::remove_reference<T>::type>>(obj);
                    if(!castedObj) {
                        std::cerr << "Failed to cast object to type " << typeid(T).name() << std::endl;
                    }
                    return castedObj->getData();
                };
            }
        }

        template<typename T>
        static T cast(const std::shared_ptr<AnyBase>& obj) {
            std::type_index type = typeid(T);
            // check if the type has been registered
            if (castFunctions.find(type) == castFunctions.end()) {
                std::cerr << "Type " << type.name() << " has not been registered" << std::endl;
                throw std::runtime_error("Type not registered");
                return EXIT_FAILURE;
            }

            // perform the cast
            std::any result = castFunctions[type](obj);
            if (result.has_value()) {
                return std::any_cast<T>(result);
            } else {
                throw std::bad_any_cast();
            }
        }

    private:
        TypeRegistry() = default;
        static std::unordered_map<std::type_index, std::string> typeNames;
        static std::unordered_map<std::type_index, castFunction> castFunctions;
    };
}


#endif //GENOGROVE_TYPEREGISTRY_HPP
