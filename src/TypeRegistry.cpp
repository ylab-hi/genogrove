#include "genogrove/TypeRegistry.hpp"

namespace genogrove {
    std::unordered_map<std::type_index, genogrove::castFunction> genogrove::TypeRegistry::castFunctions;
    std::unordered_map<std::type_index, std::string> genogrove::TypeRegistry::typeNames;

    void TypeRegistry::serialize(std::ostream& os) {
        size_t typeCount = typeNames.size();
        os.write(reinterpret_cast<const char*>(&typeCount), sizeof(typeCount));

        // serialize each type and its corresponding cast function
        for(auto& [typeIndex, typeName] : typeNames) {
            size_t typeNameLength = typeName.size();
            os.write(reinterpret_cast<const char*>(&typeNameLength), sizeof(typeNameLength));
            os.write(typeName.c_str(), typeNameLength);
        }
    }

    std::shared_ptr<AnyBase> TypeRegistry::deserialize(std::istream& is) {
        size_t typeCount;
        is.read(reinterpret_cast<char*>(&typeCount), sizeof(typeCount));

        for(size_t i=0; i < typeCount; ++i) {
            size_t typeNameLength;
            is.read(reinterpret_cast<char*>(&typeNameLength), sizeof(typeNameLength));
            std::string typeName(typeNameLength, '\0');
            is.read(&typeName[0], typeNameLength);
        }
}