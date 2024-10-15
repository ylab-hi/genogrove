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

namespace genogrove {
    class AnyBase;

    using castFunction = std::function<std::any(const std::shared_ptr<AnyBase>&)>;

    class TypeRegistry {
    public:
        // singleton pattern to ensure a single instance
        static TypeRegistry &instance() {
            static TypeRegistry instance;
            return instance;
        }

        TypeRegistry(const TypeRegistry &) = delete;
        TypeRegistry &operator=(const TypeRegistry &) = delete;

        template<typename T>
        static void registerType() {
            std::type_index typeIndex = typeid(T);
            std::string typeName = typeid(T).name();

            if (castFunctions.find(typeName) == castFunctions.end()) {
                castFunctions[typeName] = [](const std::shared_ptr<AnyBase>& obj) -> std::any {
                    auto castedObj = std::dynamic_pointer_cast<
                            AnyType<typename std::remove_reference<T>::type>>(obj);
                    if(!castedObj) {
                        std::cerr << "Failed to cast object to type " << typeid(T).name() << std::endl;
                    }
                    return castedObj->getData();
                };

                // register the type name for later serialization
                typeNames[typeIndex] = typeid(T).name(); // store the type name
            }
        }

        // cast a type back from the registered function
        template<typename T>
        static T cast(const std::shared_ptr<AnyBase>& obj) {
            std::string typeName = typeid(T).name();
            // check if the type has been registered
            if (castFunctions.find(typeName) == castFunctions.end()) {
                throw std::runtime_error("The type has not been registered");
            }

            // perform the cast
            std::any result = castFunctions[typeName](obj);
            if (result.has_value()) {
                return std::any_cast<T>(result);
            } else {
                throw std::bad_any_cast();
            }
        }

        template<typename T>
        static bool checktype(std::shared_ptr<AnyBase>& obj) {
            return typeid(T).name() == obj->getTypeName();
        }

        // getter & setter
        static std::unordered_map<std::type_index, std::string> getTypeNames();
        static std::unordered_map<std::string, castFunction> getCastFunctions();

        static void reset();

    private:
        TypeRegistry() = default;
        static std::unordered_map<std::type_index, std::string> typeNames;
        static std::unordered_map<std::string, castFunction> castFunctions;
    };
}


#endif //GENOGROVE_TYPEREGISTRY_HPP
