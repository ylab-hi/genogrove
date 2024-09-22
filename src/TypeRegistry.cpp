#include "genogrove/TypeRegistry.hpp"

namespace genogrove {
    std::unordered_map<std::type_index, genogrove::castFunction> genogrove::TypeRegistry::castFunctions;
    std::unordered_map<std::type_index, std::string> genogrove::TypeRegistry::typeNames;
}