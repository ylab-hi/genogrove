#ifndef GENOGROVE_TYPEREGISTRY_HPP
#define GENOGROVE_TYPEREGISTRY_HPP

// Standard
#include <string>
#include <unordered_map>
#include <typeindex>
#include <stdexcept>

class TypeRegistry {
    public:
        static TypeRegistry& instance() {
            static TypeRegistry instance;
            return instance;
        }

        void registerType(const std::string& typeName, const std::type_index& typeIndex) {
            typeMap[typeName] = typeIndex;
        }

        std::type_index getTypeIndex(const std::string& typeName) const {
            auto it = typeMap.find(typeName);
            if(it != typeMap.end()) {
                return it->second;
            }
            throw std::runtime_error("Type not found");
        }

    private:
        TypeRegistry() = default;
        std::unordered_map<std::string, std::type_index> typeMap;
};

#endif //GENOGROVE_TYPEREGISTRY_HPP
