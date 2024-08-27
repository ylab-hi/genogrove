#ifndef GENOGROVE_TYPEREGISTRY_HPP
#define GENOGROVE_TYPEREGISTRY_HPP

// Standard
#include <string>
#include <unordered_map>
#include <typeindex>
#include <stdexcept>
#include <any>

class TypeRegistry {
    public:
        static TypeRegistry& instance() {
            static TypeRegistry instance;
            return instance;
        }

        void registerType(const std::string& typeName, const std::type_index& typeIndex) {
            typeMap.insert(std::make_pair(typeName, typeIndex));
        }

        std::type_index getTypeIndex(const std::string& typeName) const {
            auto it = typeMap.find(typeName);
            if(it != typeMap.end()) {
                return it->second;
            }
            throw std::runtime_error("Type not found");
        }

        template<typename T>
        T cast(const std::any& value) const {
            return std::any_cast<T>(value);
        }

    private:
        TypeRegistry() = default;
        std::unordered_map<std::string, std::type_index> typeMap;
};

#endif //GENOGROVE_TYPEREGISTRY_HPP
