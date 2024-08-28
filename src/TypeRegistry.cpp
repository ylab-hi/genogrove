#include "genogrove/TypeRegistry.hpp"

namespace genogrove {
    // static members
    std::unordered_map<std::type_index, castFunction> TypeRegistry::castFunctions;

//    template<typename T>
//    static void TypeRegistry::registerType() {
//        if(castFunctions.find(typeid(T)) == castFunctions.end()) {
//            castFunctions[typeid(T)] = [](const std::shared_ptr<AnyBase>& obj) {
//                auto castedObj = std::dynamic_pointer_cast<AnyType<T>>(obj);
//            };
//        }
//    }

    void TypeRegistry::cast(const std::shared_ptr<AnyBase>& obj) {
        auto it = castFunctions.find(typeid(obj->getDataType()));
        if(it != castFunctions.end()) {
            it->second(obj);
        } else {
            std::cerr << "Type not registered " << std::endl;
        }
    }
}