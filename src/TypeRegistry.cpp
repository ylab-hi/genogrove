#include "genogrove/TypeRegistry.hpp"

namespace genogrove {
    std::unordered_map<std::string, genogrove::castFunction> genogrove::TypeRegistry::castFunctions;
    std::unordered_map<std::type_index, std::string> genogrove::TypeRegistry::typeNames;

    // getter & setter
    std::unordered_map<std::type_index, std::string> TypeRegistry::getTypeNames() { return typeNames; }
    std::unordered_map<std::string, castFunction> TypeRegistry::getCastFunctions() { return castFunctions; }

    // reset the TypeRegistry
    void TypeRegistry::reset() {
        typeNames.clear();
        castFunctions.clear();
    }
}