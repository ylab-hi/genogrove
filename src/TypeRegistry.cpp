#include "genogrove/TypeRegistry.hpp"

namespace genogrove {
    std::unordered_map<std::type_index, genogrove::castFunction> genogrove::TypeRegistry::castFunctions;
    std::unordered_map<std::type_index, std::string> genogrove::TypeRegistry::typeNames;

    void TypeRegistry::serialize(std::ostream& os, const std::type_index& typeIndex) {
        size_t typeCount = typeNames.size();
        os.write(reinterpret_cast<const char*>(&typeCount), sizeof(typeCount));

        // serialize each type and its corresponding cast function
        for(auto& [typeIndex, typeName] : typeNames) {
            os.write(reinterpret_cast<const char*>(&typeIndex), sizeof(typeIndex));
            os.write(reinterpret_cast<const char*>(&typeName), sizeof(typeName));

            if(castFunctions.find(typeIndex) != castFunctions.end()) {
                os.write(reinterpret_cast<const char*>(&castFunctions[typeIndex]), sizeof(castFunctions[typeIndex]));
            }
        }
    }

    std::shared_ptr<AnyBase> TypeRegistry::deserialize(std::istream& is) {
//        size_t nameLength;
//        is.read(reinterpret_cast<char*>(nameLength), sizeof(nameLength));
//
//        std::string typeName(nameLength, '\0');
//        is.read(&typeName[0], nameLength);
//
//        // find the matching type and function
//        for(const auto& [typeIndex, storedName] : typeNames) {
//            if(storedName == typeName) {
//                return castFunctions[typeIndex](is);
//            }
//        }
//
//        throw std::runtime_error("Unknown type in deserialization: " + typeName);
    }
}