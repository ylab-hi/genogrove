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

// Class
#include "AnyBase.hpp"

namespace genogrove {
    class AnyBase;

    using ProcessFunction = std::function<std::shared_ptr<AnyBase>(std::shared_ptr<void>)>;

    class TypeRegistry {
    public:
        static TypeRegistry &instance() {
            static TypeRegistry instance;
            return instance;
        }

        TypeRegistry(const TypeRegistry &) = delete;

        TypeRegistry &operator=(const TypeRegistry &) = delete;

        void registerType(const std::string &name, std::type_index index);

        std::type_index getType(const std::string &name) const;

    private:
        TypeRegistry() = default;

        static std::unordered_map<std::string, std::type_index> typeMap;
        static std::unordered_map<std::type_index, ProcessFunction> processFunctions;

    };
}



//            template<typename T>
//            static void registerType(const std::string &typeName) {
//                auto it = typeMap.find(typeid(T));
//                if(it != typeMap.end()) {
//                    throw std::runtime_error("Type already registered");
//                }
//                typeMap[typeid(T)] = typeName;
//                processFunctions[typeid(T)] = [](const std::shared_ptr<AnyBase>& obj) {
//                    auto castedObj = std::dynamic_pointer_cast<T>(obj);
//                    if(!castedObj) {
//                        std::cerr << "Failed to cast object to type " << typeid(T).name() << std::endl;
//                    }
//                };
//            }
//
//            static void process(const std::shared_ptr<AnyBase>& obj) {
//                auto it = processFunctions.find(typeid(*obj));
//                if(it != processFunctions.end()) {
//                    it->second(obj);
//                } else {
//                    std::cerr << "Type not registered " << std::endl;
//                }
//            }
//
//        private:
//            static std::unordered_map<std::type_index, std::string> typeMap;
//            static std::unordered_map<std::type_index, std::function<void(const std::shared_ptr<AnyBase>&)>> processFunctions;
//    };
//
//    std::unordered_map<std::type_index, std::string> TypeRegistry::typeMap;
//    std::unordered_map<std::type_index, std::function<void(const std::shared_ptr<AnyBase>&)>> TypeRegistry::processFunctions;
//}


#endif //GENOGROVE_TYPEREGISTRY_HPP
