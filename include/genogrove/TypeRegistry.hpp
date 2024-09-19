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

    template<typename T>
    using castFunction = std::function<T(const std::shared_ptr<AnyBase>&)>;

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
            if (castFunctions<T>.find(typeIndex) == castFunctions<T>.end()) {
                castFunctions<T>[typeIndex] = [](const std::shared_ptr<AnyBase>& obj) -> T {
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
            auto& typedCastFunctions = castFunctions<T>;
            // check if the type has been registered
            if(castFunctions<T>.find(type) == castFunctions<T>.end()) {
                std::cerr << "Type " << type.name() << " has not been registered" << std::endl;
                return EXIT_FAILURE;
            } else {
                return castFunctions<T>[type](obj);
            }
        }

    private:
        TypeRegistry() = default;
        static std::unordered_map<std::type_index, std::string> typeNames;
        template<typename T>
        static std::unordered_map<std::type_index, castFunction<T>> castFunctions;
    };
}

//    template<typename T>
//    std::unordered_map<std::type_index, genogrove::castFunction<T>> genogrove::TypeRegistry::castFunctions;


#endif //GENOGROVE_TYPEREGISTRY_HPP
