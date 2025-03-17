#include "genogrove/TypeRegistry.hpp"

namespace genogrove::type {
    std::unordered_map<std::string, ggt::castFunction> ggt::TypeRegistry::castFunctions;
    std::unordered_map<std::type_index, std::string> ggt::TypeRegistry::typeNames;
    std::unordered_map<std::string, ggt::factoryFunction> ggt::TypeRegistry::factoryFunctions;

    // getter & setter
    std::unordered_map<std::type_index, std::string> TypeRegistry::getTypeNames() { return typeNames; }
    std::unordered_map<std::string, castFunction> TypeRegistry::getCastFunctions() { return castFunctions; }

    // reset the TypeRegistry
    void TypeRegistry::reset() {
        typeNames.clear();
        castFunctions.clear();
    }

    std::shared_ptr<AnyBase> TypeRegistry::create(const std::string& typeName) {
        auto it = factoryFunctions.find(typeName);
        if(it != factoryFunctions.end()) {
            return it->second();
        }
        throw std::runtime_error("Type not registered: " + typeName);
    }
}