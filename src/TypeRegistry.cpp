#include "genogrove/TypeRegistry.hpp"

namespace genogrove {
    // static members
    std::unordered_map<std::string, std::type_index> TypeRegistry::typeMap;
    std::unordered_map<std::type_index, std::string> TypeRegistry::processFunctions;

    void TypeRegistry::registerType(const std::string& name, std::type_index index) {
        typeMap.insert(std::make_pair(name, index));
    }

    std::type_index TypeRegistry::getType(const std::string& name) const {
        auto it = typeMap.find(name);
        if(it != typeMap.end()) {
            return it->second;
        }
        return std::type_index(typeid(void));
    }
}