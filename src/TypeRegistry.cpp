#include "genogrove/TypeRegistry.hpp"

namespace genogrove {
    std::unordered_map<std::string, genogrove::castFunction> genogrove::TypeRegistry::castFunctions;
    std::unordered_map<std::type_index, std::string> genogrove::TypeRegistry::typeNames;
    std::unordered_map<std::string, genogrove::factoryFunction> genogrove::TypeRegistry::factoryFunctions;

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