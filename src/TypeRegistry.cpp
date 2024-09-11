#include "genogrove/TypeRegistry.hpp"

namespace genogrove {
    // static members
    std::unordered_map<std::type_index, castFunction> TypeRegistry::castFunctions;
    std::unordered_map<std::type_index, std::string> TypeRegistry::typeNames;

//    template<typename T>
//    static void TypeRegistry::registerType() {
//        if(castFunctions.find(typeid(T)) == castFunctions.end()) {
//            castFunctions[typeid(T)] = [](const std::shared_ptr<AnyBase>& obj) {
//                auto castedObj = std::dynamic_pointer_cast<AnyType<T>>(obj);
//            };
//        }
//    }

    std::any TypeRegistry::cast(const std::shared_ptr<AnyBase>& obj, std::type_index typeIndex) {
        auto it = castFunctions.find(typeIndex);
        if(it != castFunctions.end()) {
            return it->second(obj);
        } else {
            std::cerr << "Type not registered " << std::endl;
            return std::any();
        }
    }
}